#ifndef LISTMODEL_H
#define LISTMODEL_H

#include <QAbstractListModel>
#include "musicitem.h"
#include <QtCore>

class ListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    ListModel(QVector<MusicItem*> items,QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Remove data:
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

private:
    QVector<MusicItem*> m_items;
};

#endif // LISTMODEL_H
