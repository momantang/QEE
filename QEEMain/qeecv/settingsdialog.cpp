#include "settingsdialog.h"



SettingsDialog::SettingsDialog(QWidget* parent) :
    QDialog(parent)
{
    treeView = new QTreeView;
    treeView->setMinimumWidth(200);
    treeView->setMaximumWidth(200);
    treeView->setHeaderHidden(true);
    stack = new QStackedWidget;
    AOISettingWidget* aoi = new AOISettingWidget(this);
    stack->addWidget(aoi);

    QHBoxLayout* mainLayout = new QHBoxLayout;
  
    //treeView->setModel(&model);
    this->initTreeView();
    mainLayout->addWidget(treeView);
    mainLayout->addWidget(stack);

    this->setLayout(mainLayout);
    this->resize(1024, 768);
    this->setWindowTitle(tr("setting"));
}

SettingsDialog::~SettingsDialog()
{
}

void SettingsDialog::loadSettings()
{
}

void SettingsDialog::saveSettings()
{
}

void SettingsDialog::initTreeView()
{
    treeModel = new QStandardItemModel(this);
    QStandardItem* rootNode = treeModel->invisibleRootItem();

    QStandardItem* aoiItem = new QStandardItem("AOI");
    QStandardItem* aoi1Item = new QStandardItem("AOI1");
    QStandardItem* aoi2Item = new QStandardItem("AOI2");
    QStandardItem* aoi3Item = new QStandardItem("AOI3");
    QStandardItem* aoi4Item = new QStandardItem("AOI4");

    rootNode->appendRow(aoiItem);
    rootNode->appendRow(aoi1Item);
    rootNode->appendRow(aoi2Item);
    rootNode->appendRow(aoi3Item);
    rootNode->appendRow(aoi4Item);

    treeView->setModel(treeModel);



}

AOISettingWidget::AOISettingWidget(QWidget* parent)
{
    QFormLayout *mainLayout = new QFormLayout;

    imagepathLineEdit = new QLineEdit;
    blurSizeSpinBox = new QSpinBox;
    mainLayout->addRow(tr("Image Path"), imagepathLineEdit);
    mainLayout->addRow(tr("Blur Size"), blurSizeSpinBox);
    this->setLayout(mainLayout);
}

AOISettingWidget::~AOISettingWidget()
{
}
