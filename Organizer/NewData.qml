import QtQuick 2.13
import QtQuick.Controls 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.3


Rectangle {
    color: '#eeeee4'
    width: 600
    height: 120
    id:mainrect
    property int numTasks: 0;
    property var tempDate: new Date();
    DatePicker{
        id: dialogCalendar
    }
    //Name
    Text {
        id: _lbTaskName
        anchors.left: mainrect.left
        anchors.leftMargin: 5
        anchors.top: mainrect.top
        anchors.topMargin: 5
        text: qsTr("Task")
        //horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        width: 70
        height: 25

    }
    Rectangle
    {
       color: 'white'
       anchors.left: _lbTaskName.right
       anchors.leftMargin: 5
       anchors.top: _lbTaskName.top
       width: taskName.width
       height: taskName.height
    }

    TextInput{
       id:taskName
       anchors.left: _lbTaskName.right
       anchors.leftMargin: 5
       anchors.top: _lbTaskName.top
       width: 400
       focus: true
       height: 25
       verticalAlignment: Text.AlignVCenter
       validator: RegExpValidator{regExp: /[а-яА-Яa-zA-Z0-9]+/}
    }
    //Date
    Text {
        id: _lbTaskDate
        anchors.left: _lbTaskName.left
        anchors.top: _lbTaskName.bottom
        anchors.topMargin: 5
        text: qsTr("Date")
        //horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        width: _lbTaskName.width
        height: _lbTaskName.height
    }
    Rectangle
    {
       color: 'white'
       anchors.left: _lbTaskDate.right
       anchors.leftMargin: 5
       anchors.top: _lbTaskDate.top
       width: taskDate.width
       height: taskDate.height
    }

    TextInput{
        id:taskDate
        anchors.left: _lbTaskDate.right
        anchors.leftMargin: 5
        anchors.top: _lbTaskDate.top
        width: 400
        focus: true
        height: 25
        verticalAlignment: Text.AlignVCenter
        text: Qt.formatDate(tempDate, "dd.MM.yyyy");
        MouseArea{
            anchors.fill: parent
            acceptedButtons: Qt.LeftButton
            onClicked:
            {
                dialogCalendar.show()
            }
        }
    }

    //Progress
    Text {
        id: _lbTaskProgress
        anchors.left: _lbTaskDate.left
        anchors.top: _lbTaskDate.bottom
        anchors.topMargin: 5
        text: qsTr("Progress")
 //       style: Text.Outline
        //horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        width: _lbTaskName.width
        height: _lbTaskName.height
    }
    Rectangle
    {
       color: 'white'
       anchors.left: _lbTaskProgress.right
       anchors.leftMargin: 5
       anchors.top: _lbTaskProgress.top
       width: taskProgress.width
       height: taskProgress.height
    }
    property string prevProgress: ""
    TextInput{
       id:taskProgress
       anchors.left: _lbTaskProgress.right
       anchors.leftMargin: 5
       anchors.top: _lbTaskProgress.top
       width: 400
       focus: true
       height: 25
       verticalAlignment: Text.AlignVCenter
       text: "0"
       validator: IntValidator{bottom: 0; top:10}
       onTextChanged:
       {
           if(text) {
               if (!acceptableInput)
               {
                   text = prevProgress
               }
               prevProgress = text
           }
       }
    }

    MessageDialog {
        id: messageDialog
        title: qsTr("Error")
        icon: StandardIcon.Warning
        standardButtons: StandardButton.Close
    }

   AddButton{
       id:addData
       anchors.top: taskName.top
       anchors.bottom: taskProgress.bottom
       anchors.left: taskProgress.right
       anchors.leftMargin: 5
       anchors.right: mainrect.right
       anchors.rightMargin: 5
       //text: qsTr("Add")
       onClicked:
       {
           if(!taskName.acceptableInput)
           {
               messageDialog.text = qsTr("Enter task name")
               messageDialog.open()
               return
           }

           var name = taskName.text
           var date = taskDate.text
           var progress = taskProgress.text
           mainrect.parent.add(name, date, progress)
       }
   }
   Text {
       id: _lbTotalTasks
       anchors.left: _lbTaskProgress.left
       anchors.top: _lbTaskProgress.bottom
       anchors.topMargin: 5
       text: qsTr("Total Tasks")
       //horizontalAlignment: Text.AlignHCenter
       verticalAlignment: Text.AlignVCenter
       width: _lbTaskName.width
       height: _lbTaskName.height

   }
   Text {
       id: _TotalTasks
       anchors.left: _lbTotalTasks.right
       anchors.leftMargin: 5
       anchors.top: _lbTotalTasks.top
       text: numTasks
       //horizontalAlignment: Text.AlignHCenter
       verticalAlignment: Text.AlignVCenter
       width: 400
       height: 25

   }



}
