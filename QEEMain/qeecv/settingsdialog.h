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

#include <QAbstractItemModel>
#include <QModelIndex>

///
///参考 Qt6.2.3 中的例子 simpletreemodel
/// 


class TreeItem {
public:
	explicit TreeItem(const QList<QVariant>& data, TreeItem* parentItem = nullptr);
	~TreeItem();

	void appendChild(TreeItem* child);
	TreeItem* child(int row);
	int childCount()const;
	int columnCount() const;
	QVariant data(int column) const;
	int row()const;
	TreeItem* parentItem();
private:
	QList<TreeItem*> m_childItems;
	QList<QVariant> m_itemData;
	TreeItem* m_parentItem;
};
class TreeModel :public QAbstractItemModel {
	Q_OBJECT
public:
	explicit TreeModel(const QString& data, QObject* parent = nullptr);
	~TreeModel();
	Qt::ItemFlags flags(const QModelIndex& index) const override;
	QVariant headerData(int section, Qt::Orientation orientation,
		int role = Qt::DisplayRole) const override;

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;

	QModelIndex parent(const QModelIndex& child) const override;

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;

	int columnCount(const QModelIndex& parent = QModelIndex()) const override;

private:
	void setupModelData(const QStringList& lines, TreeItem* parent);
	TreeItem* rootItem;







};



class SettingsDialog : public QDialog
{
	Q_OBJECT

public:
	explicit SettingsDialog(QWidget* parent = nullptr);
	~SettingsDialog();

private:
	QListWidget* listWidget;
	QStackedWidget* stack;
	QTreeView* treeView;

};

#endif // SETTINGSDIALOG_H
