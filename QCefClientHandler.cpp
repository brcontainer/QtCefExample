#include "stdafx.h"
#include "QCefClientHandler.h"
#include "qcefmessageevent.h"

namespace
{
	QCefClientHandler * g_instance = nullptr;
}

QCefClientHandler::QCefClientHandler() :
	isClosing_(false)
{
	g_instance = this;

	if (startupUrl_.empty()) {
		startupUrl_ = "about:blank";
	}
}

QCefClientHandler::~QCefClientHandler()
{
	g_instance = nullptr;
}

// static
QCefClientHandler * QCefClientHandler::GetInstance()
{
	return g_instance;
}

void QCefClientHandler::OnAfterCreated(CefRefPtr<CefBrowser> browser)
{
	CEF_REQUIRE_UI_THREAD();

	browserList_.push_back(browser);
}

bool QCefClientHandler::DoClose(CefRefPtr<CefBrowser> browser)
{
	CEF_REQUIRE_UI_THREAD();

	if (browserList_.size() == 1) {
		isClosing_ = true;
	}

	return true;
}

void QCefClientHandler::OnBeforeClose(CefRefPtr<CefBrowser> browser)
{
	CEF_REQUIRE_UI_THREAD();

	BrowserList::iterator bit = browserList_.begin();
	for (; bit != browserList_.end(); ++bit) {
		if ((*bit)->IsSame(browser)) {
			browserList_.erase(bit);
			break;
		}
	}

	if (browserList_.empty()) {
		CefQuitMessageLoop();
	}
}

void QCefClientHandler::OnLoadError(CefRefPtr<CefBrowser> browser, 
									CefRefPtr<CefFrame> frame, 
									ErrorCode errorCode, 
									const CefString& errorText, 
									const CefString& failedUrl)
{
	CEF_REQUIRE_UI_THREAD();

	// Don't display an error for downloaded files.
	if (errorCode == ERR_ABORTED)
		return;

	// Display a load error message.
	std::stringstream ss;
	ss << "<html><body bgcolor=\"white\">"
		"<h2>Failed to load URL " << std::string(failedUrl) <<
		" with error " << std::string(errorText) << " (" << errorCode <<
		").</h2></body></html>";
	frame->LoadString(ss.str(), failedUrl);
}

void QCefClientHandler::CloseAllBrowsers(bool force_close)
{
	if (!CefCurrentlyOn(TID_UI)) {
		// Execute on the UI thread.
		CefPostTask(TID_UI,
					base::Bind(&QCefClientHandler::CloseAllBrowsers, this, force_close));
		return;
	}

	if (browserList_.empty())
		return;

	BrowserList::const_iterator it = browserList_.begin();
	for (; it != browserList_.end(); ++it)
		(*it)->GetHost()->CloseBrowser(force_close);
}

// static
void QCefClientHandler::CreateProcessMessageDelegates(ProcessMessageDelegateSet& delegates)
{
	client_binding::CreateProcessMessageDelegates(delegates);
}