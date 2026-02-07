#pragma once
#include "utils.h"
#include <include/cef_parser.h>
#include <include/cef_resource_handler.h>
#include <filesystem>
#include "fstream"
#include "string"

class NanoFileResourceHandler : public CefResourceHandler
{
public:
	bool Open(
		CefRefPtr<CefRequest> pRequest,
		bool& handleRequest,
		CefRefPtr<CefCallback> pCallback
	) override
	{
		handleRequest = true;
		CefURLParts urlParts;
		CefParseURL(pRequest->GetURL(), urlParts);
		const auto path = std::filesystem::path{ CefString(&urlParts.path).ToString() }.relative_path();
		uintmax_t& shit = (uintmax_t&)(fileSize_);
		std::filesystem::_File_size(path, shit);
		auto ext = path.extension().string();
		ext.erase(std::remove(ext.begin(), ext.end(), '.'), ext.end());
		if (!ext.empty())
		{
			fileMimeType_ = CefGetMimeType(ext);
		}

		fileStream_ = std::ifstream{ path, std::ios::binary };
		return bool(fileStream_);
	}

	void GetResponseHeaders(
		CefRefPtr<CefResponse> pResponse,
		int64_t& responselenght,
		CefString& redirectUrl
	) override
	{
		if (!fileMimeType_.empty())
		{
			pResponse->SetMimeType(fileMimeType_);
		}
		pResponse->SetStatus(200);
		responselenght = fileSize_;
	}

	bool Read(
		void* dataOut,
		int bytesToRead,
		int& bytesRead,
		CefRefPtr<CefResourceReadCallback> pCallback
	) override
	{
		if (!dataOut)
		{
			bytesRead = -2;
			return false;
		}

		fileStream_.read(static_cast<char*>(dataOut), bytesToRead);

		bytesRead = int(fileStream_.gcount());

		return bytesRead > 0;
	}

	void Cancel() override
	{

	}
private:
	std::ifstream fileStream_;
	int64_t fileSize_ = 0;
	std::string fileMimeType_;

	IMPLEMENT_REFCOUNTING(NanoFileResourceHandler);

};