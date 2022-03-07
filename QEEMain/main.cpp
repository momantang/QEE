#include "mainwindow.h"
#include "cv/cvmainwindow.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CVMainWindow w;
    w.show();
    return a.exec();
}
