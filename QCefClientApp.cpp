#include "stdafx.h"
#include "QCefClientApp.h"
#include "QCefClientHandler.h"

QCefClientApp::QCefClientApp()
{
}

void QCefClientApp::OnContextInitialized()
{
	CEF_REQUIRE_UI_THREAD();

	// Information used when creating the native window.
	CefWindowInfo window_info;

#if defined(OS_WIN)
	// On Windows we need to specify certain flags that will be passed to
	// CreateWindowEx().
	window_info.SetAsPopup(nullptr, "cefsimple");
#endif

	// QCefClientHandler implements browser-level callbacks.
	CefRefPtr<QCefClientHandler> handler(new QCefClientHandler());

	// Specify CEF browser settings here.
	CefBrowserSettings browser_settings;

	std::string url;

	// Check if a "--url=" value was provided via the command-line. If so, use
	// that instead of the default URL.
	CefRefPtr<CefCommandLine> command_line =
		CefCommandLine::GetGlobalCommandLine();
	url = command_line->GetSwitchValue("url");
	if (url.empty())
		url = "http://www.google.com";

	// Create the first browser window.
	CefBrowserHost::CreateBrowser(window_info, handler.get(), url,
								  browser_settings, NULL);
}
