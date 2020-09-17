#include "customlistmodel.h"

CustomListModel::CustomListModel(QObject *parent):
    QStandardItemModel(parent){
}

CustomListModel::CustomListModel(int rows, int columns, QObject *parent = nullptr):
    QStandardItemModel(rows, columns, parent){

}

Qt::ItemFlags CustomListModel::flags (const QModelIndex & index) const {
    Qt::ItemFlags defaultFlags = QStandardItemModel::flags(index);
    if (index.isValid()){
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsEditable;
    }
    return defaultFlags;
}

//void CustomListModel::save(){
//    QFile file("sorts.txt");
//    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
//        return;

//    QTextStream out(&file);
//    out << "Types of sorts:" << "\n";

//    QListIterator<QString> it(this->stringList());
//    while(it.hasNext())
//        out << it.next() << "\n";

//}
