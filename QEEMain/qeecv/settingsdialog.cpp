#include "settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent)
{
    treeView = new QTreeView;
    treeView->setMinimumWidth(200);
    treeView->setMaximumWidth(200);
    stack = new QStackedWidget;
    
    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->addWidget(treeView);
    mainLayout->addWidget(stack);

    this->setLayout(mainLayout);
    this->resize(1024, 768);
    this->setWindowTitle(tr("setting"));
}

SettingsDialog::~SettingsDialog()
{
   
}
