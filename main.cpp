#include "stdafx.h"
#include "qtcefexample.h"
#include "QCefClient.h"
#include "qcefwebview.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);


	int result = QCefInit(argc, argv);
	if (result >= 0) {
		return result;
	}

	QtCefExample w;
	w.resize(800, 600);

	QCefWebView * cefWebView = new QCefWebView(&w);
	w.setCentralWidget(cefWebView);

	w.show();

	return a.exec();
}
