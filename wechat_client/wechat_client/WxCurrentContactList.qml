import QtQuick 2.3
import QtQuick.Controls 2.4

Item {
    id: wxCurrentContactList

    property alias user_list: user_model_data
    property string color_list_back: "#292d32"
    property string color_item_back: "#2e3238"
    property string color_item_hover: "#3b4047"

    signal itemClicked(string _user_name)
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

            model: ListModel {
                id: user_model_data
            }

            ScrollBar.vertical: ScrollBar {
            }

            delegate: Rectangle {
                id: dlt
                width: parent.width
                height: 65
                color: color_item_back

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
                    onEntered: dlt.color = color_item_hover
                    onExited: dlt.color = color_item_back
                    onClicked: onItemPressed(_user_name)
                }
            }
        }
    }

    function onItemPressed(user_name){
        //print(user_name)
        itemClicked(user_name)
    }
}
