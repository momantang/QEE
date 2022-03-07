#include "b23mw.h"
#include "ui_b23mw.h"

B23MW::B23MW(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::B23MW)
{
    ui->setupUi(this);
}

B23MW::~B23MW()
{
    delete ui;
}
