#pragma once

#include <QtWidgets>
#include "audiodialog.h"

class QEEMain : public QMainWindow
{
    Q_OBJECT

public:
    QEEMain(QWidget *parent = Q_NULLPTR);

private:
    AudioDialog* dlg;
    QPushButton* button;
};
