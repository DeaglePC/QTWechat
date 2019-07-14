import QtQuick 2.0

Item {
    id: wxChat
    width: 500
    height: 500
    property alias nickName: chatNick.text
    property alias msgDataList: chatList.chatDataList
    property string userName: ""
    property string selfHead: ""

    property string color_topbar_back: "#d0e9ff"
    property string color_chat_back: "#eeeeee"

    Rectangle {
        id: charWarp
        anchors.fill: parent
        color: color_chat_back
        Rectangle {
            id: chatTopBar
            width: parent.width
            height: 50
            color: color_chat_back
            Text {
                id: chatNick
                //text: qsTr("text")
                height: 30
                anchors.centerIn: parent
            }
            Rectangle {
                id: borderTopBar
                anchors.bottom: parent.bottom
                width: parent.width - 20
                height: 1
                color: "#d6d6d6"
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }

        WxChatList {
            id: chatList
            anchors.top: chatTopBar.bottom
            anchors.topMargin: 10
            width: parent.width
            height: parent.height - chatTopBar.height - anchors.topMargin
            focus: true
        }
    }
}
