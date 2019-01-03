import QtQuick 2.0

Item {
    id: wxChatFormRight
    property alias head: head_image.source
    property alias textComponent: content.sourceComponent

    width: 300
    height: 50
    Rectangle {
        id: formWarp
        color: "transparent"
        anchors.fill: parent

        Rectangle {
            id: contentWarp
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: head_image.left
            anchors.rightMargin: 15
            /*Loader {
                id: content
            }*/
            Text{
                anchors.fill: parent
                text: "123123"
            }
        }

        Image {
            id: head_image
            width: 40
            height: 40
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
        }
    }
}
