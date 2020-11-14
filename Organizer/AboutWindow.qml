import QtQuick 2.0
import QtQuick.Window 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
Window {
    id:infoWindow
    width: 500
    height: 200
    function setInformation(name, date, progress)
    {
        title = name
        _date.text = date
        _progress.text = progress

    }
    ColumnLayout{
        //anchors.fill: parent
        Text{
            id: _date
            focus: true
            wrapMode: TextEdit.Wrap
        }
        Text{
            id: _progress
            focus: true
            wrapMode: TextEdit.Wrap
        }
    }
}
