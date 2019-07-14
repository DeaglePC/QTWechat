import QtQuick 2.0
import QtQuick.Controls 2.4

Item {
    id: wxChatList
    property alias chatDataList: chatWindow

    width: 600
    height: 400

    Rectangle {
        id: warp
        anchors.fill: parent
        color: "transparent"

        ListView {
            id: lv
            anchors.fill: parent
            orientation: ListView.Vertical
            spacing: 10
            clip: true

            ScrollBar.vertical: ScrollBar {
            }

            model: ListModel{
                id: chatWindow
            }

            delegate: Loader {
                property string dataHead: _head
                property string dataMsgContent: _msg_content
                //property int dataMsgStatus: _msg_status
                //property string dataMsgId: _msg_id
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
            width: lv.width
            height: leftChatMsgForm.height
            color: "transparent"

            WxChatFormLeft {
                id: leftChatMsgForm
                head: dataHead
                msgContent: dataMsgContent
                anchors.left: parent.left
                anchors.leftMargin: 10
                anchors.top: parent.top
            }
        }
    }

    Component {
        id: delegateRight
        Rectangle {
            width: lv.width
            height: rightChatMsgForm.height
            color: "transparent"
            //color: "#22e2e2"

            WxChatFormRight {
                id: rightChatMsgForm
                head: dataHead
                msgContent: dataMsgContent
                msgStatus: dataMsgStatus
                anchors.right: parent.right
                anchors.rightMargin: 10
                anchors.top: parent.top
            }
        }
    }
}
