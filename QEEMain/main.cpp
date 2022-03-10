#include "QEEMain.h"
#include "qeecv/cvmainwindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator* translator = new QTranslator;
    translator->load("D:/QEE/QEEMain/qeemain_zh.qm");
    a.installTranslator(translator);
    CVMainWindow w;
    w.show();
    return a.exec();
}
