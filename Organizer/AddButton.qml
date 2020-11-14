import QtQuick 2.0

BorderImage {
    id: name

    signal clicked

    source: "qrc:///img/Unpressed.png"
    width: 100; height: 100
    border.left: 5; border.top: 5
    border.right: 5; border.bottom: 5
    MouseArea{
        anchors.fill: parent
        onClicked: parent.clicked()
        onPressed: {
            source = "qrc:///img/Pressed.png"
        }
        onReleased: {
            source = "qrc:///img/Unpressed.png"
        }
    }


}
