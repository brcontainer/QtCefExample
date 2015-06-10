#pragma once

#ifndef QCEFCLIENTAPP_H
#define QCEFCLIENTAPP_H

class QCefClientApp : 
	public CefApp,
	public CefBrowserProcessHandler
{
public:
	QCefClientApp();

	// CefApp methods:
	virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler()
		OVERRIDE{ return this; }

	// CefBrowserProcessHandler methods:
	virtual void OnContextInitialized() OVERRIDE;

private:
	// Include the default reference counting implementation.
	IMPLEMENT_REFCOUNTING(QCefClientApp);
};

#endif // QCEFCLIENTAPP_H
