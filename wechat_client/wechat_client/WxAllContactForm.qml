import QtQuick 2.0
import QtGraphicalEffects 1.0

Item {
    id:wxAllContactForm
    property alias nick: nick_name.text
    property alias head: head_image.source
    property alias head_image_item: head_image
    property string user_name
    property string pyname: ""
    property int head_radius: 5

    width: 280
    height: 30

    Row {
        anchors.fill: parent
        spacing: 10
        Image {
            id: head_image
            width: 30
            height: 30
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
        Text {
            id: nick_name
            width: 240
            height: 30
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 13
            verticalAlignment: Text.AlignVCenter
            textFormat: TextEdit.RichText
            color: "#fff"
        }
    }

}
