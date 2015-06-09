#include "stdafx.h"
#include "qtcefexample.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QtCefExample w;
	w.show();
	return a.exec();
}
