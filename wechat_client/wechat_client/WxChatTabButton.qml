import QtQuick 2.0

Item {
    id: wxChatTabButton
    property string image_source : "res/main_source.png"
    property string color_back: "#2e3238"
    property string color_border: "#24272c"
    property string color_hover_color: "#3a3f45"

    signal chatTabBtnClicked()
    signal publicTabBtnClicked()
    signal friendsTabBtnClicked()

    width: 280
    height: 35

    Rectangle{
        anchors.fill: parent
        color: color_back
        Row {
            // chat
            Rectangle {
                id: warp_chat
                width: wxChatTabButton.width / 3
                height: wxChatTabButton.height
                color:"transparent";
                Loader{
                    id: btn_chat_white
                    sourceComponent: img_chat_white
                    anchors.horizontalCenter: parent.horizontalCenter
                    visible: false
                }
                Loader{
                    id: btn_chat_green
                    sourceComponent: img_chat_green
                    anchors.horizontalCenter: parent.horizontalCenter
                    visible: true
                }

                MouseArea{
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered: warp_chat.color = color_hover_color
                    onExited: warp_chat.color = "transparent"
                    onClicked: chatClickProc()
                }
            }
            // border
            Rectangle{
                width: 1
                height: 25
                color: color_border
                anchors.verticalCenter: parent.verticalCenter
            }
            // public
            Rectangle {
                id: warp_public
                width: wxChatTabButton.width / 3
                height: wxChatTabButton.height
                color:"transparent";
                Loader{
                    id: btn_public_white
                    sourceComponent: img_public_white
                    anchors.horizontalCenter: parent.horizontalCenter
                    visible: true
                }
                Loader{
                    id: btn_public_green
                    sourceComponent: img_public_green
                    anchors.horizontalCenter: parent.horizontalCenter
                    visible: false
                }

                MouseArea{
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered: warp_public.color = color_hover_color
                    onExited: warp_public.color = "transparent"
                    onClicked: publicClickProc()
                }
            }
            // border
            Rectangle{
                width: 1
                height: 25
                color: color_border
                anchors.verticalCenter: parent.verticalCenter
            }
            // firends
            Rectangle {
                id: warp_friends
                width: wxChatTabButton.width / 3
                height: wxChatTabButton.height
                color:"transparent";
                Loader{
                    id: btn_friends_white
                    sourceComponent: img_friends_white
                    anchors.horizontalCenter: parent.horizontalCenter
                    visible: true
                }
                Loader{
                    id: btn_friends_green
                    sourceComponent: img_friends_green
                    anchors.horizontalCenter: parent.horizontalCenter
                    visible: false
                }

                MouseArea{
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered: warp_friends.color = color_hover_color
                    onExited: warp_friends.color = "transparent"
                    onClicked: friendsClickProc()
                }
            }
        }
    }

    // 6个图标
    Component{
        id: img_chat_white
        UtilClipImage {
            source_image: image_source
            pos_x: -151
            pos_y: -96
            width: 35
            height: 35
        }
    }

    Component{
        id: img_chat_green
        UtilClipImage {
            source_image: image_source
            pos_x: -185
            pos_y: -96
            width: 35
            height: 35
        }
    }

    Component{
        id: img_public_white
        UtilClipImage {
            source_image: image_source
            pos_x: -376
            pos_y: -322
            width: 35
            height: 35
        }
    }

    Component{
        id: img_public_green
        UtilClipImage {
            source_image: image_source
            pos_x: -305
            pos_y: -281
            width: 35
            height: 35
        }
    }

    Component{
        id: img_friends_white
        UtilClipImage {
            source_image: image_source
            pos_x: -220
            pos_y: -96
            width: 35
            height: 35
        }
    }

    Component{
        id: img_friends_green
        UtilClipImage {
            source_image: image_source
            pos_x: -304
            pos_y: -246
            width: 35
            height: 35
        }
    }
    // 6个图标


    // 点击事件处理
    // 改变图标是白色或者绿色 status = 1 绿色, 0 白色
    // type = 0(chat), 1(public), 2(friends)
    function iconChange(type, status){
        var obj_green
        var obj_white
        if (type === 0){
            obj_green = btn_chat_green
            obj_white = btn_chat_white
        }else if(type === 1){
            obj_green = btn_public_green
            obj_white = btn_public_white
        }else if(type === 2){
            obj_green = btn_friends_green
            obj_white = btn_friends_white
        }

        if (status === 1){
            obj_white.visible = false
            obj_green.visible = true
        }else{
            obj_white.visible = true
            obj_green.visible = false
        }
    }

    function chatClickProc(){
        iconChange(0, 1)
        iconChange(1, 0)
        iconChange(2, 0)
        chatTabBtnClicked()
    }

    function publicClickProc(){
        iconChange(0, 0)
        iconChange(1, 1)
        iconChange(2, 0)
        publicTabBtnClicked()
    }

    function friendsClickProc(){
        iconChange(0, 0)
        iconChange(1, 0)
        iconChange(2, 1)
        friendsTabBtnClicked()
    }
}
