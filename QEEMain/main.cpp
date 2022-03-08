#include "QEEMain.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QEEMain w;
    w.show();
    return a.exec();
}
