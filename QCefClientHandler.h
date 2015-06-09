#pragma once

#include "qcefmessageevent.h"

class QCefClientHandler :
	public CefClient,
	public CefDisplayHandler,
	public CefLifeSpanHandler,
	public CefLoadHandler
{
public:
	class Listener
	{
	public:
		virtual ~Listener() {};

		virtual void OnAddressChange(const QString & url) = 0;
		virtual void OnTitleChange(const QString & title) = 0;
		virtual void SetLoading(bool isLoading) = 0;
		virtual void SetNavState(bool canGoBack, bool canGoForward) = 0;
		virtual void OnAfterCreated() = 0;
		virtual void OnMessageEvent(QCefMessageEvent * e) = 0;
	};

	QCefClientHandler();
	virtual ~QCefClientHandler();

	static QCefClientHandler * GetInstance();

	// CefClient methods
	virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler() OVERRIDE{
		return this;
	}
	virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() OVERRIDE{
		return this;
	}
	virtual CefRefPtr<CefLoadHandler> GetLoadHandler() OVERRIDE{
		return this;
	}
	
	bool IsClosing() const
	{
		return isClosing_; 
	};

	CefRefPtr<CefBrowser> GetBrowser()
	{
		return browser_;
	}

	void setListener(Listener* listener)
	{
		listener_ = listener;
	}
	Listener* listener() const
	{
		return listener_;
	}

private:
	typedef std::list<CefRefPtr<CefBrowser>> BrowserList;
	BrowserList browserList_;

	bool isClosing_;

	// The child browser window
	CefRefPtr<CefBrowser> browser_;

	// Listener interface
	Listener* listener_;

	IMPLEMENT_REFCOUNTING(QCefClientHandler);
};

