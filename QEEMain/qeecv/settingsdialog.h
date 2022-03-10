#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QSettings>
#include <QSharedPointer>
#include <qlistwidget.h>
#include <qstackedwidget.h>
#include <QTreeView>
#include <QtWidgets>
class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog();

private:
    QListWidget* listWidget;
    QStackedWidget* stack;
    QTreeView* treeView;

};

#endif // SETTINGSDIALOG_H
