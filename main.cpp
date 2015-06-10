#include "stdafx.h"
#include "qtcefexample.h"
#include "qcefwebview.h"
#include "QCefClientApp.h"

bool IsSubprocess(int & argc, char ** argv)
{
	std::vector<std::string> argVector(argv, argv + argc);

	for (auto i = 0; i < argc; ++i) {
		if (argVector[i].find("--type") != std::string::npos) {
			return true;
		}
	}

	return false;
}

int RunCef()
{
	void* sandbox_info = nullptr;

	HINSTANCE hInstance = static_cast<HINSTANCE>(GetModuleHandle(nullptr));

	CefMainArgs main_args(hInstance);

	CefRefPtr<QCefClientApp> app(new QCefClientApp);

	// run subprocess
	int exit_code = CefExecuteProcess(main_args, app.get(), nullptr);
	if (exit_code >= 0) {
		return exit_code;
	}

	CefSettings settings;
	settings.no_sandbox = true;

	CefInitialize(main_args, settings, app.get(), nullptr);

	CefRunMessageLoop();

	CefShutdown();

	return 0;
}

int RunCefSubprocess(int &, char **)
{
	CefMainArgs cefMainArgs(GetModuleHandle(nullptr));

	return CefExecuteProcess(cefMainArgs, nullptr, nullptr);
}

int main(int argc, char *argv[])
{
	if (IsSubprocess(argc, argv)) {
		return RunCefSubprocess(argc, argv);
	}
	else {
		RunCef();

		QApplication a(argc, argv);

		QtCefExample w;
		w.resize(800, 600);


		//	QCefWebView * cefWebView = new QCefWebView(&w);
		//	w.setCentralWidget(cefWebView);

		w.show();

		a.exec();

	}
}
