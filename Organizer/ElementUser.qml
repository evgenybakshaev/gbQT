import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

Rectangle {
    property string taskname: ""    // Свойства объекта
    property string taskdate: ""
    property string taskprogress: ""
//    function setValue(t, inf)
//    {
//       console.log(t + inf)
//    }

    id: root
    color: '#eeeee4'
    width: 600
    height: 25

    //anchors.fill: parent


    Text {
       id:_name
       text: taskname
       verticalAlignment: Text.AlignVCenter
       width: 200
       height: root.height
       anchors.left: root.left
       anchors.leftMargin: 5
    }

    Text {
       id: _date
       text: taskdate
       verticalAlignment: Text.AlignVCenter
       width: 100
       height: root.height
       anchors.left: _name.right
       anchors.leftMargin: 5
    }
    Text {
       id: _progress
       text: taskprogress
       verticalAlignment: Text.AlignVCenter
       width: 100
       height: root.height
       anchors.left: _date.right
       anchors.leftMargin: 5
    }

    MouseArea {
       acceptedButtons: Qt.LeftButton
       anchors.fill: parent
       cursorShape: "PointingHandCursor"
       onClicked: {
           var component = Qt.createComponent("AboutWindow.qml")
           var obj = component.createObject(root)
           obj.setInformation(taskname, taskdate, taskprogress)
           obj.show()

       }
    }
}
