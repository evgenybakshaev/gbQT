#ifndef CUSTOMLISTMODEL_H
#define CUSTOMLISTMODEL_H
#include <QStandardItemModel>

class CustomListModel : public QStandardItemModel
{
public:
    CustomListModel(QObject* parent = Q_NULLPTR);
    CustomListModel(int rows, int columns, QObject *parent);
    Qt::ItemFlags flags (const QModelIndex& index) const;
    //void save();
};

#endif // CUSTOMLISTMODEL_H
