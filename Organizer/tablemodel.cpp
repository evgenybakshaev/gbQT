#include "tablemodel.h"

QHash<int, QByteArray> TableModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    for (int i = 0; i < record().count(); i ++) {
        roles.insert(Qt::UserRole + i + 1, record().fieldName(i).toUtf8());
    }
    return roles;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    QVariant value;
    if (index.isValid()) {
        if (role < Qt::UserRole) {
            value = QSqlQueryModel::data(index, role);
        } else {
            int columnIdx = role - Qt::UserRole - 1;
            QModelIndex modelIndex = this->index(index.row(), columnIdx);
            value = QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
        }
    }
    return value;
}

QString TableModel::queryStr() const{
    return query().lastQuery();
}

void TableModel::setQueryStr(const QString &query){
    if(queryStr() == query)
        return;
    setQuery(query);
    emit queryStrChanged();
}

QStringList TableModel::userRoleNames() const {
    QStringList names;
    for (int i = 0; i < record().count(); i ++) {
        names << record().fieldName(i).toUtf8();
    }
    return names;
}

void TableModel::updateModel()
{
    this->setQuery("SELECT * FROM tasklist");
}

int TableModel::getId(int row)
{
    int IdRole = Qt::UserRole + 1;
    for(int i = 0; i < record().count(); i++)
    {
        if(record().fieldName(i).toUtf8() == "id")
            IdRole += i;
    }
    return this->data(this->index(row, 0), IdRole).toInt();
}
