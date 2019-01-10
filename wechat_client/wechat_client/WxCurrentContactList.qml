import QtQuick 2.3
import QtQuick.Controls 2.4

Item {
    id: wxCurrentContactList

    property alias user_list: user_model_data
    property string color_list_back: "#292d32"
    property string color_item_back: "#2e3238"
    property string color_item_hover: "#3b4047"

    property int lastSlectIndex: -1

    signal itemClicked(string _user_name, string _head)
    signal userHeadImgStatusChanged(string _user_name, int _status, string _head)

    width: 280
    height: 600

    Rectangle {
        color: color_list_back
        anchors.fill: parent
        ListView {
            id: lv
            anchors.fill: parent
            orientation: ListView.Vertical
            spacing: 1
            clip: true
            focus: true

            model: ListModel {
                id: user_model_data
            }

            ScrollBar.vertical: ScrollBar {
            }

            delegate: Rectangle {
                id: dlt
                property bool _select_color: false
                width: parent.width
                height: 65
                color:{
                    if(_select_color){
                        "#989898"
                    }
                    else{
                        color_item_back
                    }
                }

                WxCurrentContactForm {
                    id: user_info_delt
                    anchors.left: parent.left
                    anchors.leftMargin: 18
                    nick: _nick
                    head: _head
                    time: _time
                    last_msg: _last_msg
                    user_name: _user_name
                    anchors.verticalCenter: parent.verticalCenter
                    head_image_item.onStatusChanged: {userHeadImgStatusChanged(_user_name, head_image_item.status, _head)}
                }

                MouseArea {
                    hoverEnabled: true
                    anchors.fill: parent
                    onEntered: {
                        dlt.color = color_item_hover
                        user_info_delt.color_last_msg = "#fff"
                    }
                    onExited: {
                        dlt.color = color_item_back
                        user_info_delt.color_last_msg = "#989898"
                    }
                    onClicked: {
                        lv.currentIndex = index
                        if (lastSlectIndex !== -1){
                            user_model_data.get(lastSlectIndex)["_select_color"] = false
                        }
                        _select_color = true

                        lastSlectIndex = index
                        onItemPressed(_user_name, _head)
                    }
                }
            }
        }
    }

    function onItemPressed(user_name, head){
        //print(user_name)
        //print(head)
        itemClicked(user_name, head)
    }
}
