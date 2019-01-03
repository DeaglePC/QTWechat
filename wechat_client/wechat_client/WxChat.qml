import QtQuick 2.0

Item {
    id: wxChat
    width: 500
    height: 500

    Rectangle {
        id: charWarp
        anchors.fill: parent
        color: "gray"
        Rectangle {
            id: chatTopBar
            width: parent.width
            height: 50
            Text {
                id: charNick
                text: qsTr("text")
                height: 30
                anchors.centerIn: parent
            }
            Rectangle {
                id: borderTopBar
                anchors.bottom: parent.bottom
                width: parent.width - 50
                height: 1
                color: "green"
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }

    }

}
