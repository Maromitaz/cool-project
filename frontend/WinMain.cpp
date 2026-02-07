#include "utils.h"

void fromCstrToWstr(const char* src, WCHAR* dest, size_t destSize)
{
	mbstowcs_s(nullptr, dest, destSize, src, destSize - 1);
}

extern LRESULT BrowserWindowWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	const CefMainArgs mainArgs{ hInstance };
	CefRefPtr<NanoCefApp> pApp = new NanoCefApp();
	if (const auto code = CefExecuteProcess(mainArgs, pApp, nullptr); code >= 0)
	{
		return (int)code;
	}

	CefSettings settings;
	settings.multi_threaded_message_loop = true;
	CefString(&(settings.cache_path)).FromString((std::filesystem::current_path() / "cef_cache").string());

	CefInitialize(mainArgs, settings, pApp, nullptr);

	const char* wndClassName = "Client";
	const WCHAR* name[100]{};
	fromCstrToWstr(wndClassName, (WCHAR*)name, sizeof(name) / sizeof(WCHAR));
	HWND hWndWindow = nullptr;
	{
		WNDCLASSEXA wcex{};
		wcex.cbSize = sizeof(wcex);
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = BrowserWindowWndProc;
		wcex.hInstance = hInstance;
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		wcex.lpszClassName = wndClassName;
		RegisterClassExA(&wcex);

		hWndWindow = CreateWindowExA(
			0, wndClassName, (LPCSTR)name,
			WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, 200, 20,
			1360, 1020, nullptr, nullptr, hInstance, nullptr
		);

		ShowWindow(hWndWindow, SW_SHOWDEFAULT);
		UpdateWindow(hWndWindow);
	}

	MSG msg;
	while (GetMessageA(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	CefShutdown();


	return (int)msg.wParam;
}