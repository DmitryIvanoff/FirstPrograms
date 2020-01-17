#include "listmodel.h"


ListModel::ListModel(QVector<MusicItem *> items, QObject *parent): QAbstractListModel(parent)
{
    if (!items.empty())
    {
            m_items=items;
    }
}

QVariant ListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role!=Qt::DisplayRole)
    {
        QVariant();
    }
    return (orientation == Qt::Horizontal)? QString("Number"):QString::number(section);

}

int ListModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;
    return m_items.size();
}

QVariant ListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    return (role == (Qt::DisplayRole||Qt::EditRole)) ? m_items.at(index.row()): QVariant();
}



bool ListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    for (int i=0;i<count;++i)
    {
        m_items.removeAt(row);
    }
    endRemoveRows();
}
