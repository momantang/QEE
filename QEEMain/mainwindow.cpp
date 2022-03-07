#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "cv/cvmainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("QEE");

    connect(ui->actionCVMainWindow,&QAction::triggered,this,[=](){
        CVMainWindow::inst()->show();
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}

