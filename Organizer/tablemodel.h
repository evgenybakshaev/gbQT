#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlRecord>

 class TableModel : public QSqlQueryModel
 {
     Q_OBJECT
     Q_PROPERTY(QString query READ queryStr WRITE setQueryStr NOTIFY queryStrChanged)
     Q_PROPERTY(QStringList userRoleNames READ userRoleNames CONSTANT)

//     enum Roles {
//             IdRole = Qt::UserRole + 1,     // id
//             NameRole,                      // задача
//             DateRole,                      // дата
//             ProgressRole                   // прогресс
//         };

 public:
     using QSqlQueryModel::QSqlQueryModel;
     QHash<int, QByteArray> roleNames() const;
     QVariant data(const QModelIndex &index, int role) const;
     QString queryStr() const;
     void setQueryStr(const QString &query);
     QStringList userRoleNames() const;

 public slots:
     void updateModel();
     int getId(int row);
 signals:
     void queryStrChanged();
 };

#endif // TABLEMODEL_H
