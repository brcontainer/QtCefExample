#include "stdafx.h"
#include "qcefwebview.h"

const QString QCefWebView::kUrlBlank = "about:blank";

QCefWebView::QCefWebView(QWidget *parent) : 
	QWidget(parent),
	browserState_(kNone),
	needResize_(false),
	needLoad_(false)
{
	setAttribute(Qt::WA_NativeWindow, true);
	setAttribute(Qt::WA_DontCreateNativeAncestors, true);
}

QCefWebView::~QCefWebView()
{
	// empty destructor
}

void QCefWebView::load(const QUrl& url)
{
	url_ = url;
	
	switch (browserState_) {
		case kNone:
			CreateBrowser(size());
			break;

		case kCreating:
			needLoad_ = true;
			break;

		default:
			BrowserLoadUrl(url);
	}
}

void QCefWebView::setHtml(const QString& html, const QUrl& baseUrl)
{
	if (GetBrowser().get()) {
		QUrl url = baseUrl.isEmpty() ? this->url() : baseUrl;

		if (!url.isEmpty()) {
			auto frame = GetBrowser()->GetMainFrame();
			frame->LoadStringW(CefString(html.toStdWString()),
							   CefString(url.toString().toStdWString()));
		}
	}
}

QUrl QCefWebView::url() const
{
	if (GetBrowser().get()) {
		auto url = GetBrowser()->GetMainFrame()->GetURL();
		return QUrl(QString::fromStdWString(url.ToWString()));
	}
	return QUrl();
}

void QCefWebView::back()
{
	auto browser = GetBrowser();

	if (browser.get()) {
		browser->GoBack();
	}
}

void QCefWebView::forward()
{
	auto browser = GetBrowser();

	if (browser.get()) {
		browser->GoForward();
	}
}

void QCefWebView::reload()
{
	auto browser = GetBrowser();

	if (browser.get()) {
		browser->Reload();
	}
}

void QCefWebView::stop()
{
	auto browser = GetBrowser();

	if (browser.get()) {
		browser->StopLoad();
	}
}

void QCefWebView::resizeEvent(QResizeEvent* event)
{
	switch (browserState_) {
		case kNone:
			CreateBrowser(event->size());
			break;

		case kCreating:
			needResize_ = true;
			break;

		default:
			ResizeBrowser(event->size());
	}
}

void QCefWebView::closeEvent(QCloseEvent* event)
{

}
