import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.4
import QtMultimedia 5.8
import cn.deaglepc.wx 1.0
import "js/contact.js" as Contact
import "js/work.js" as Work
import "js/message.js" as Message

Window {
    id: root
    visible: true
    title: qsTr("wechat-dpc")

    property int screen_width: Screen.width
    property int screen_height: Screen.height

    property var allFriendsDict: ({})

    CLibWebwx {
        id: wx
    }

    // login ui
    WxLogin {
        id: login
        visible: false
    }
    // login ui end

    // main ui
    Rectangle {
        id: mainUi
        anchors.fill: parent
        Rectangle {
            id: userPanelCol
            width: 280
            height: root.height
            anchors.left: mainUi.left
            Rectangle {
                id: userPanelWarp
                anchors.fill: parent
                color: "#2e3238"
                WxTopBar {
                    id: topBar
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                WxSearchBar {
                    id: searchBar
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: topBar.bottom
                    //anchors.topMargin: 10
                }
                WxChatTabButton {
                    id: chatTabButton
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: searchBar.bottom
                    anchors.topMargin: 5
                    onChatTabBtnClicked: Work.onChatBtnClicked()
                    onFriendsTabBtnClicked: Work.onFriendsBtnClicked()
                }
                // 最近联系人列表
                Rectangle {
                    id: borderTmp
                    color: "#24272c"
                    width: parent.width
                    height: 1
                    anchors.top: chatTabButton.bottom
                }

                WxCurrentContactList {
                    id: currentContactList
                    anchors.left: parent.left
                    anchors.top: borderTmp.bottom
                    anchors.topMargin: 1
                    height: parent.height - topBar.height - searchBar.height -
                            chatTabButton.height - chatTabButton.anchors.topMargin -
                            anchors.topMargin - borderTmp.height
                }

                WxAllContactList {
                    id: allContactList
                    anchors.left: parent.left
                    anchors.top: borderTmp.bottom
                    anchors.topMargin: 1
                    height: parent.height - topBar.height - searchBar.height -
                            chatTabButton.height - chatTabButton.anchors.topMargin -
                            anchors.topMargin - borderTmp.height
                    visible: false
                }
            }
        }

        Rectangle {
            id: messagePanelCol
            height: root.height
            width: root.width - userPanelCol.width
            anchors.right: mainUi.right
            visible: false

            WxChat {
                id: wxChat
                width: parent.width
                height: parent.height - sendRect.height - borderChat.height
            }

            Rectangle {
                id: borderChat
                height: 1
                width: parent.width
                color: "#d6d6d6"
                anchors.top: wxChat.bottom
            }

            WxChatSend {
                id: sendRect
                anchors.top: borderChat.bottom
                width: parent.width
                height: 160
            }

            // test
            /*MouseArea {
                anchors.fill: parent
                onClicked: {
                    print("=====")
                    wxChat.nickName = "dog"
                    wxChat.msgDataList.append({"_is_left": false, "_head": "res/ldh.jpg", "_msg_content":"cao"})
                    wxChat.msgDataList.append({"_is_left": true, "_head": "res/ldh.jpg", "_msg_content":"cao"})
                }
            }*/
        }
    }
    // main ui end

    Audio {
        id: audioMsg
        source: "res/msg.mp3"
    }

    Component.onCompleted: {
        Work.runWx()
        //Work.test()
    }

    Connections {
        target: wx
        onSglQrcodeOk: {login.qrcode = link}
        onSglHintMsg: Work.dealHintMsg(msg_type, msg)
        onSglAllContactOk: Contact.dealAllContact(allContact)
        onSglOneHeadOk: Contact.addContactHead(headFileName)
        onSglGetUserselfFinished: Contact.addUserselfData(strUserselfData)
        onSglGG: Work.gameOver()
        onSglNewMessage: Message.dealMessage(newMsg)
        onSglSendMsgFinished: Message.sendTextMsgFinished(retContent)
    }

    Connections {
        target: allContactList
        onUserHeadImgStatusChanged: Contact.allContactImgStatusChanged(_user_name, _status, _head)
    }

    Connections {
        target: currentContactList
        onUserHeadImgStatusChanged: Contact.allContactImgStatusChanged(_user_name, _status, _head)
        onItemClicked: {
            Work.showChatMsgPanel()
            Message.showChatMsg(_user_name, _head)
        }
    }

    Connections {
        target: sendRect
        onSendClicked: Message.sendTextMsg(_content)
    }
}
