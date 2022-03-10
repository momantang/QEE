#include "settingsdialog.h"





TreeItem::TreeItem(const QList<QVariant>& data, TreeItem* parentItem):m_itemData(data),m_parentItem(parentItem)
{
}

TreeItem::~TreeItem()
{
    qDeleteAll(m_childItems);
}

void TreeItem::appendChild(TreeItem* child)
{
    m_childItems.append(child);
}

TreeItem* TreeItem::child(int row)
{
    if (row < 0 || row >= m_childItems.size())
        return nullptr;
    return m_childItems.at(row);
}

int TreeItem::childCount() const
{
    return m_childItems.count();
}

int TreeItem::columnCount() const
{
    return m_itemData.count();
}

QVariant TreeItem::data(int column) const
{
    if (column < 0 || column >= m_itemData.size())
    return QVariant();
    return m_itemData.at(column);
}

int TreeItem::row() const
{
    if (m_parentItem)
        return m_parentItem->m_childItems.indexOf(const_cast<TreeItem*>(this));

    return 0;
}

TreeItem* TreeItem::parentItem()
{
    return m_parentItem;
}

TreeModel::TreeModel(const QString& data, QObject* parent):QAbstractItemModel(parent)
{
    rootItem = new TreeItem({ tr("title") });
    setupModelData(data.split("\n"), rootItem);
}

TreeModel::~TreeModel()
{
    delete rootItem;
}

Qt::ItemFlags TreeModel::flags(const QModelIndex& index) const
{
    return Qt::ItemFlags();
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

QVariant TreeModel::data(const QModelIndex& index, int role) const
{
    return QVariant();
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex& parent) const
{
    return QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex& child) const
{
    return QModelIndex();
}

int TreeModel::rowCount(const QModelIndex& parent) const
{
    return 0;
}

int TreeModel::columnCount(const QModelIndex& parent) const
{
    return 0;
}

void TreeModel::setupModelData(const QStringList& lines, TreeItem* parent)
{
    QList<TreeItem*>parents;
    QList<int> indentations;
    parents << parent;
    indentations << 0;

    int number = 0;

}

SettingsDialog::SettingsDialog(QWidget* parent) :
    QDialog(parent)
{
    treeView = new QTreeView;
    treeView->setMinimumWidth(200);
    treeView->setMaximumWidth(200);
    stack = new QStackedWidget;

    QHBoxLayout* mainLayout = new QHBoxLayout;
    QFile file("D:/Qt/Examples/Qt-6.2.3/widgets/itemviews/simpletreemodel/default.txt");
    TreeModel model(file.readAll());
    treeView->setModel(&model);
    mainLayout->addWidget(treeView);
    mainLayout->addWidget(stack);

    this->setLayout(mainLayout);
    this->resize(1024, 768);
    this->setWindowTitle(tr("setting"));
}

SettingsDialog::~SettingsDialog()
{
}
