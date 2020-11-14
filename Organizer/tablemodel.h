#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <qqml.h>
#include <QAbstractTableModel>

 class TableModel : public QAbstractTableModel
 {
     Q_OBJECT
     QML_ELEMENT
     QML_ADDED_IN_MINOR_VERSION(1)
     enum TableRoles{
         TableDataRole = Qt::UserRole + 1,
         HeadingRole
     };
 public:
     explicit TableModel(QObject *parent = nullptr);
     int rowCount(const QModelIndex & = QModelIndex()) const override;
     int columnCount(const QModelIndex & = QModelIndex()) const override;
     QVariant data(const QModelIndex &index, int role) const override;
     QHash<int, QByteArray> roleNames() const override;
     bool setData(const QModelIndex &index, const QVariant &value, int role) override;
 private:
     QVector<QVector<QString>> table;
 };

#endif // TABLEMODEL_H
