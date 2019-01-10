import QtQuick 2.0
import QtGraphicalEffects 1.0

Item {
    id: wxChatFormLeft
    property alias head: head_image.source
    property alias msgContent: content.text
    property int contentMaxWidth: 300

    width: head_image.width + contentWarp.width + contentWarp.anchors.leftMargin
    height: Math.max(contentWarp.height, head_image.height)

    Rectangle {
        id: formWarp
        color: "transparent"
        anchors.fill: parent

        Image {
            id: head_image
            width: 40
            height: 40
            anchors.top: parent.top
            anchors.left: parent.left

            // 圆角化
            property bool rounded: true
            property bool adapt: true

            layer.enabled: rounded
            layer.effect: OpacityMask {
                maskSource: Item {
                    width: head_image.width
                    height: head_image.height
                    Rectangle {
                        anchors.centerIn: parent
                        width: head_image.adapt ? head_image.width : Math.min(head_image.width,
                                                                head_image.height)
                        height: head_image.adapt ? head_image.height : width
                        //radius: Math.min(width, height)
                        radius: 5
                    }
                }
            }
        }

        Rectangle {
            id: contentWarp
            anchors.top: parent.top
            anchors.left: head_image.right
            anchors.leftMargin: 10
            width: content.paintedWidth + 20
            height: content.paintedHeight + 18
            color: "#fff"
            radius: 5

            Text{
                id: content
                anchors.right: parent.right
                anchors.rightMargin: 10
                anchors.verticalCenter: parent.verticalCenter
                wrapMode: Text.WordWrap
                onPaintedWidthChanged: {
                    content.width = Math.min(contentMaxWidth, content.paintedWidth)
                }
            }
        }
    }
}
