#include "stdafx.h"

#include "QCefClientHandler.h"

void QCefClientHandler::OnTitleChange(CefRefPtr<CefBrowser> browser,
									  const CefString& title)
{
	CEF_REQUIRE_UI_THREAD();

	CefWindowHandle hwnd = browser->GetHost()->GetWindowHandle();
	SetWindowText(hwnd, std::wstring(title).c_str());
}
