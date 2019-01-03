import QtQuick 2.0

Item {
    id: wxChatFormLeft
    property alias head: head_image.source
    property alias textComponent: content.sourceComponent

    Rectangle {
        id: formWarp
        color: "transparent"

        Image {
            id: head_image
            width: 40
            height: 40
            anchors.left: parent.left
        }

        Rectangle {
            id: contentWarp
            anchors.left: head_image.right
            anchors.leftMargin: 15
            Loader {
                id: content
            }
        }
    }
}
