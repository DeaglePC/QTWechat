import QtQuick 2.0
import QtQuick.Controls 2.4

Item {
    id: wxChatSend
    property alias sendContent: content.text

    property string color_chat_back: "#eeeeee"

    width: 500
    height: 500

    Rectangle{
        id: warp
        anchors.fill: parent
        border.color: "green"
        border.width: 2

        Rectangle {
            id: toolBar
            height: 30
            width: parent.width
            color: color_chat_back
        }

        Rectangle {
            id: inputBox
            anchors.top: toolBar.bottom
            width: parent.width
            height: parent.height - toolBar.height - bottomBar.height
            color: color_chat_back

            ScrollView {
                id: view
                anchors.fill: parent

                TextArea {
                    id: content
                    selectionColor: "green"
                    focus: true
                    selectByMouse: true
                }
            }
        }

        Rectangle {
            id: bottomBar
            height: 40
            width: parent.width
            anchors.top: inputBox.bottom
            color: color_chat_back

            Button {
                id: btnSend
                width: 88
                height: 30
                anchors.rightMargin: 20
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                text: qsTr("发送")

                contentItem: Text {
                    text: btnSend.text
                    font: btnSend.font
                    color: "#fff"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight
                }

                background: Rectangle {
                      implicitWidth: 100
                      implicitHeight: 40
                      opacity: 0.6
                      color: btnSend.down ? "#17a81a" : "#21be2b"
                      border.color: "green"
                      border.width: 1
                      radius: 2
                }
            }
        }
    }
}
