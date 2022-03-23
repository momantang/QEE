#include "QEEMain.h"
//#include "audiosource.h"
#include "qeecv/cvmainwindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	QTranslator* translator = new QTranslator;
	bool isTranslator=translator->load("D:/QEE/QEEMain/qeemain_zh.qm");
	a.installTranslator(translator);
	CVMainWindow w;
	//InputTest w;
	w.show();
	return a.exec();
}
