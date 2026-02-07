#pragma once
#include "utils.h"
#include <include/cef_scheme.h>
#include "ResourceHandler.h"

class NanoFileSchemeHandlerFactory : public CefSchemeHandlerFactory
{
	CefRefPtr<CefResourceHandler> Create(
		CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		const CefString& scheme_name,
		CefRefPtr<CefRequest> request
	) override
	{
		return new NanoFileResourceHandler{};
	}

	IMPLEMENT_REFCOUNTING(NanoFileSchemeHandlerFactory);
};