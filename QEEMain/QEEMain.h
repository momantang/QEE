#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QEEMain.h"

class QEEMain : public QMainWindow
{
    Q_OBJECT

public:
    QEEMain(QWidget *parent = Q_NULLPTR);

private:
    Ui::QEEMainClass ui;
};
