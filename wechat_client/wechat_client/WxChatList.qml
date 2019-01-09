import QtQuick 2.0

Item {
    id: wxChatList
    property alias chatDataList: chatWindow
    property string userName: ""

    property string color_chat_back: "#eeeeee"

    width: 600
    height: 400

    Rectangle {
        id: warp
        anchors.fill: parent
        color: color_chat_back

        ListView {
            id: lv
            anchors.fill: parent
            orientation: ListView.Vertical
            spacing: 2
            clip: true

            model: ListModel{
                id: chatWindow
            }

            delegate: Loader {
                sourceComponent: {
                    if(_is_left) delegateLeft
                    else delegateRight
                }
            }
        }
    }

    Component {
        id: delegateLeft
        Rectangle {
            width: parent.width
            height: leftChatMsgForm.height

            WxChatFormLeft {
                id: leftChatMsgForm
                width: 500
                head: _head
                msgContent: _msg_content
            }
        }
    }

    Component {
        id: delegateRight
        Rectangle {
            width: parent.width
            height: rightChatMsgForm.height

            WxChatFormRight {
                id: rightChatMsgForm
                width: 500
                head: _head
                msgContent: _msg_content
            }
        }
    }
}
