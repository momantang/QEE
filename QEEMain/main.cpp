#include "QEEMain.h"
#include "qeecv/cvmainwindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CVMainWindow w;
    w.show();
    return a.exec();
}
