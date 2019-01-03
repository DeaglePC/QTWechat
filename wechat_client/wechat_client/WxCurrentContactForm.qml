import QtQuick 2.0
import QtQuick.Controls 2.4
import QtGraphicalEffects 1.0

Item {
    id: wxCurrentContactForm

    property alias head_image_item: head_image
    property alias head: head_image.source
    property alias nick: name.text
    property alias last_msg: last_msg.text
    property alias time: time.text
    property string user_name
    property int head_radius: 5

    property string color_text: "#fff"
    property string color_last_msg: "#989898"

    width: 245
    height: 40

    Row {
        id: warp
        anchors.fill: parent
        spacing: 10
        Image {
            id: head_image
            width: 40
            height: 40
            anchors.verticalCenter: parent.verticalCenter

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
                        radius: head_radius
                    }
                }
            }
        }

        Column {
            anchors.verticalCenter: parent.verticalCenter
            Row {
                Text {
                    id: name
                    width: 155
                    height: 20
                    anchors.verticalCenter: parent.verticalCenter
                    color: color_text
                    clip: true
                }
                Text {
                    id: time
                    width: warp.width - last_msg.width - warp.spacing - head_image.width
                    height: 20
                    anchors.verticalCenter: parent.verticalCenter
                    color: color_last_msg
                    clip: true
                    font.pixelSize: 11
                }
            }
            Row {
                Text {
                    id: last_msg
                    width: 162
                    height: 20
                    anchors.verticalCenter: parent.verticalCenter
                    color: color_last_msg
                    clip: true
                    font.pixelSize: 13
                }
                Text {
                    width: warp.width - last_msg.width - warp.spacing - head_image.width
                    height: 20
                    anchors.verticalCenter: parent.verticalCenter
                    color: color_last_msg
                    clip: true
                }
            }
        }
    }
}
