import QtQuick 2.0
import QtGraphicalEffects 1.0

Item {
    id: wxTopBar

    property alias head_image_url: head_image.source
    property alias nick_name: nick_name_text.text
    property string user_name: ""
    property string json_data: ""   // 全部信息的json字符串
    property int head_radius: 5

    property string color_front: "#fff"
    property string color_back: "#2e3238"
    property string image_source : "res/main_source.png"

    width: 244
    height: 76

    Rectangle {
        anchors.fill: parent
        color: color_back
        Rectangle {
            anchors.fill: parent
            color: "transparent"
            Image {
                id: head_image
                width: 40
                height: 40
                anchors.verticalCenter: parent.verticalCenter
                source: "res/ldh.jpg"

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
            Rectangle {
                id: nick_name_warp
                width: 156
                height: 31
                color: "transparent"
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: head_image.right
                anchors.leftMargin: 10

                Text {
                    id: nick_name_text
                    text: qsTr("liudehua")
                    color: color_front
                    anchors.verticalCenter: parent.verticalCenter
                }
            }
            UtilClipImage {
                id: btn_setting
                width: 30
                height: 30
                pos_x: -434
                pos_y: -398
                source_image: image_source
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: nick_name_warp.right

                MouseArea {
                    anchors.fill: parent
                    cursorShape:Qt.ClosedHandCursor
                }
            }
        }
    }
}
