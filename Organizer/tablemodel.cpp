#include "tablemodel.h"
#include <QDate>

TableModel::TableModel(QObject *parent) : QAbstractTableModel(parent)
{
    table.append({"Task","Date","Progress"});
    table.append({"Task 1",QDate(2020,11,10).toString("dd.MM.yyyy"),"8"});
    table.append({"Task 2",QDate(2020,11,11).toString("dd.MM.yyyy"),"5"});
    table.append({"Task 3",QDate(2020,11,12).toString("dd.MM.yyyy"),"0"});
}

int TableModel::rowCount(const QModelIndex &) const
{
    return table.size();
}

int TableModel::columnCount(const QModelIndex &) const
{
    return table.at(0).size();
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    switch (role) {
    case TableDataRole:
        return table.at(index.row()).at(index.column());
        break;
    case HeadingRole:
        if(index.row() == 0) return true;
        else return false;

        break;
    default:
        break;
    }

    return QVariant();
}

QHash<int, QByteArray> TableModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TableDataRole] = "tabledata";
    roles[HeadingRole] = "heading";
    return roles;
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    //if (!index.isValid() || !indexInRange(index)) return false;
    switch (role) {
        case TableDataRole:
//             if (index.column()== 0)    m_variables[index.row()]->setName(value.toString());
//             else                       m_variables[index.row()]->setValue(value);
            table[index.row()][index.column()]= value.toString();
            break;
        default:
            return false;
    }

    emit dataChanged(index, index, {role});
    return true;
}
