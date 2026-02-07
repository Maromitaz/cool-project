#pragma once
#include "utils.h"
#include "FileSchemeHandler.h"

class NanoCefApp : public CefApp,
	public CefBrowserProcessHandler
{
	CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override
	{
		return this;
	}

	void OnContextInitialized() override
	{
		CefRegisterSchemeHandlerFactory("http", "disk", new NanoFileSchemeHandlerFactory{});
	}
	IMPLEMENT_REFCOUNTING(NanoCefApp);
};
