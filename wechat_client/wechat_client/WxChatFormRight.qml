import QtQuick 2.0

Item {
    id: wxChatFormRight
    property alias head: head_image.source
    //property alias textComponent: content.sourceComponent
    property alias msgContent: content.text

    width: head_image.width + contentWarp.width + 15
    height: contentWarp.height + 20

    Rectangle {
        id: formWarp
        color: "transparent"
        anchors.fill: parent

        Rectangle {
            id: contentWarp
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: head_image.left
            anchors.rightMargin: 10
            width: content.width + 20
            height: content.height + 10
            color: "#b2e281"
            /*Loader {
                id: content
                anchors.centerIn: parent
            }*/
            Text{
                id: content
                //text: "123123656516513136"
                anchors.centerIn: parent
                wrapMode: Text.WordWrap
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
