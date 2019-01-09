import QtQuick 2.0

Item {
    id: wxChatFormLeft
    property alias head: head_image.source
    //property alias textComponent: content.sourceComponent
    property alias msgContent: content.text

    width: head_image.width + contentWarp.width + 15
    height: contentWarp.height + 20

    Rectangle {
        id: formWarp
        color: "transparent"
        anchors.fill: parent

        Image {
            id: head_image
            width: 40
            height: 40
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
        }

        Rectangle {
            id: contentWarp
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: head_image.right
            anchors.leftMargin: 10
            width: content.width + 20
            height: content.height + 10
            color: "#fff"
            /*Loader {
                id: content
                anchors.centerIn: parent
            }*/
            Text{
                id: content
                //text: "123136"
                anchors.centerIn: parent
                wrapMode: Text.WordWrap
            }
        }
    }
}
