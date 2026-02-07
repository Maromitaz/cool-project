#include "utils.h"

using namespace std::literals;
CefRefPtr<NanoCefClient> pClient;

LRESULT BrowserWindowWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE: {
		pClient = new NanoCefClient{};

		RECT rect{};
		GetClientRect(hWnd, &rect);
		CefRect cefRect;
		cefRect.x = rect.left;
		cefRect.y = rect.right;
		cefRect.width = rect.right - rect.left;
		cefRect.height = rect.bottom - rect.top;

		CefWindowInfo info;
		info.SetAsChild(hWnd, cefRect);

		CefBrowserHost::CreateBrowser(info, pClient, "http://disk/" DEBUG_ASSETS_FOLDER "/index.html"s, {}, {}, {});
		break;
	}
	case WM_DESTROY:
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	case WM_SIZE:
		if (wParam != SIZE_MINIMIZED && pClient)
		{
			if (auto pBrowser = pClient->GetBrowser())
			{
				if (auto hWndBrowser = pBrowser->GetHost()->GetWindowHandle())
				{
					RECT rect{};
					GetClientRect(hWnd, &rect);
					SetWindowPos(hWndBrowser, NULL, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, SWP_NOZORDER);
				}
			}
		}
		break;
	case WM_ERASEBKGND:
		if (wParam != SIZE_MINIMIZED && pClient)
		{
			if (auto pBrowser = pClient->GetBrowser())
			{
				if (pBrowser->GetHost()->GetWindowHandle())
				{
					return 1;
				}
			}
		}
		break;
	default:break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}