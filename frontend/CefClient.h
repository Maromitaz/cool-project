#pragma once
#include "utils.h"

class NanoCefClient : public CefClient,
	public CefLifeSpanHandler
{
public:
	CefRefPtr<CefBrowser> GetBrowser()
	{
		return this->pBrowser_;
	}
private:
	CefRefPtr<CefBrowser> pBrowser_;
	CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override
	{
		return this;
	}

	void OnAfterCreated(CefRefPtr<CefBrowser> pBrowser) override
	{
		this->pBrowser_ = pBrowser;
	}

	IMPLEMENT_REFCOUNTING(NanoCefClient);
};
