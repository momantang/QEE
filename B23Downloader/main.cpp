#include "B23Downloader.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    B23Downloader w;
    w.show();
    return a.exec();
}
