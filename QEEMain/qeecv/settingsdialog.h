#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H
#include <QString>
#include <QDialog>
#include <QSettings>
#include <QSharedPointer>
#include <qlistwidget.h>
#include <qstackedwidget.h>
#include <QTreeView>
#include <QtWidgets>

#include <QVariant>
#include <QList>

#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QModelIndex>

class  AOISettingWidget :public QWidget {
	Q_OBJECT
public:
	explicit AOISettingWidget(QWidget* parent = nullptr);
	~AOISettingWidget();

private:

	QLineEdit *imagepathLineEdit;
	QSpinBox* blurSizeSpinBox;
};

class SettingsDialog : public QDialog
{
	Q_OBJECT

public:
	explicit SettingsDialog(QWidget* parent = nullptr);
	~SettingsDialog();
	void loadSettings();
	void saveSettings();
private:
	void initTreeView();
private:
	//QListWidget* listWidget;
	QStackedWidget* stack;
	QTreeView* treeView;
	QStandardItemModel* treeModel;

};

#endif // SETTINGSDIALOG_H
