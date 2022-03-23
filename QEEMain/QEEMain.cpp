#include "QEEMain.h"

QEEMain::QEEMain(QWidget *parent)
    : QMainWindow(parent)
{
    button = new QPushButton("Audio Widget", this);
    this->setCentralWidget(button);
   
    
    connect(button, &QPushButton::clicked, this, [this]() {
        dlg = new AudioDialog(this);
        qDebug() << " pushbutton click";
        this->dlg->show();
        });
}
