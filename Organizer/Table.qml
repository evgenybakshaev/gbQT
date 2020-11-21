import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2
import TableModel 1.0
import BaseDBReader 1.0

Window {
    id: _wndTable
    visible: true
    width: 410
    height: 200
    title: qsTr("Tasks")


    TableModel{
        id: sqlmodel
        query: "select * from tasklist"
    }
    Component{
        id: columnComponent
        TableViewColumn{width: 100 }
    }
    TableView {
        id: tableView
        anchors.fill: parent
        resources:{
            var roleList = sqlmodel.userRoleNames
            var temp = []
            for(var i in roleList){
                var role  = roleList[i]
                if(role !== "id")
                    temp.push(columnComponent.createObject(tableView, { "role": role, "title": role}))
            }
            return temp
        }
        model: sqlmodel

        // Настройка строки в TableView для перехавата левого клика мыши
//        rowDelegate: Rectangle {
//            anchors.fill: parent
//            color: styleData.selected ? 'skyblue' : (styleData.alternate ? 'whitesmoke' : 'white');
//            MouseArea {
//                anchors.fill: parent
//                acceptedButtons: Qt.RightButton | Qt.LeftButton
//                onClicked: {
//                    tableView.selection.clear()
//                    tableView.selection.select(styleData.row)
//                    tableView.currentRow = styleData.row
//                    tableView.focus = true

//                    switch(mouse.button) {
//                    case Qt.RightButton:
//                        contextMenu.popup() // Вызываем контексткное меню
//                        break
//                    default:
//                        break
//                    }
//                }
//            }
//        }
//    }
//    // Контекстно меню предлагает удаление строки из базы данных
//    Menu {
//        id: contextMenu

//        MenuItem {
//            text: qsTr("Delete")
//            onTriggered: {
//                /* Вызываем диалоговое окно,
//                 * которое уточнит намерение удалить строку из базы данных
//                 * */
//                dialogDelete.open()
//            }
//        }
//    }

//    // Диалог подтверждения удаления строки из базы данных
//    MessageDialog {
//        id: dialogDelete
//        title: qsTr("Удаление записи")
//        text: qsTr("Подтвердите удаление записи из журнала")
//        icon: StandardIcon.Warning
//        standardButtons: StandardButton.Ok | StandardButton.Cancel

//        // При положительном ответе ...
//        onAccepted: {
//            /* ... удаляем строку по id,
//             * который забираем из модели данных
//             * по номеру строки в представлении
//             * */
//            _wndTable.parent.deleteRec(sqlmodel.getId(tableView.currentRow))
//            sqlmodel.updateModel();  // Обновляем модель данных
//        }
    }

}
