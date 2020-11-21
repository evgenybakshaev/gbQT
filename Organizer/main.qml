import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import BaseDBReader 1.0                             // Подключаем наш
                                                           // класс
import QtQuick.Controls 2.5

Window {
  id:root                                                  // Имя объекта для
                                                           // обращения
   visible: true
   width: 640
   height: 480
   title: qsTr("Organizer")
// Обратите внимание на ElementUser, NewData - компоненты, созданные в QML
   property string sc: 'ElementUser{ ' // Шаблон для
                                                            // создания нового
                                                            // компонента
   property string nc: 'NewData{}'

   property int num: 0
   property NewData newData: value

   function addThisDate(name, date, progress)
   {
       loader.writeNewInformation(name, date, progress)
       var itog = sc + 'taskname:"' + name + '";taskdate:"' + date + '";taskprogress:"' + progress + '"}'
       newData.numTasks = num
       var el = Qt.createQmlObject(itog, list, "obj" + num++)
   }

   function deleteRec(row)
   {
       console.log(row)
   }

   BaseDBReader{
        id : loader
        onInitEnd:
        {
           if (succeed)           // См. объявление сигнала initEnd
        // Добавляем компонент для добавления нового города
           {
               newData = Qt.createQmlObject(nc, list, "objdata")
               var itog = sc + 'taskname:qsTr("Task");taskdate:qsTr("Date");taskprogress:qsTr("Progress")}'
                                      // Формируем описание нового элемента
               var el = Qt.createQmlObject(itog, list, "obj" + num++)
               loader.getRecords()            // Запрашиваем у класса информацию о городе
           } else Qt.quit()
        }

        onLoadTask: {
           var itog = sc + 'taskname:"' + name + '";taskdate:"' + date + '";taskprogress:"' + progress + '"}'
                                  // Формируем описание нового элемента
           newData.numTasks = num
           var el = Qt.createQmlObject(itog, list, "obj" + num++)
        }
//        onDeleteTask: {
//            list.destroy()
//            loader.loadBase()
//        }

   }
   ScrollView {
       id: sv
       ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
       ScrollBar.vertical.policy: ScrollBar.AlwaysOn
       anchors.fill: parent       // Заполняем всю область родительского
                                  // объекта
       Component.onCompleted: loader.loadBase()
       ColumnLayout {
            id:list

            function add(name, date, progress) {
               root.addThisDate(name, date, progress)
            }
       }
   }

}
