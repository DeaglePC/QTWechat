import QtQuick 2.0
import QtQuick.Controls 2.4

Item {
    id: wxAllContactList

    property alias user_list: user_model_data
    property string color_sec_back: "#292d32"
    property string color_sec_front: "#787b87"
    property string color_list_back: "#292d32"
    property string color_item_back: "#2e3238"
    property string color_item_hover: "#3b4047"

    signal itemClicked(string _user_name)
    signal userHeadImgStatusChanged(string _user_name, int _status, string _head)

    Component {
        id: sectionHeader
        Rectangle {
            width: parent.width
            height: 24
            color: color_sec_back
            Label {
                color: color_sec_front
                text: section
                font.bold: true
                font.pixelSize: 14
                anchors.left: parent.left
                anchors.leftMargin: 18
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }

    height: 600
    width: 280
    Rectangle{
        color: color_list_back
        anchors.fill: parent
        ListView {
            id: lv
            anchors.fill: parent
            orientation: ListView.Vertical
            spacing: 2
            clip: true

            section.property: "_pyname";
            section.criteria: ViewSection.FirstCharacter//ViewSection.FullString/FirstCharacter
            section.delegate: sectionHeader

            model: ListModel {
                id: user_model_data
            }

            ScrollBar.vertical: ScrollBar {
            }

            delegate: Rectangle {
                id: dlt
                width: parent.width
                height: 50
                color: color_item_back

                WxAllContactForm {
                    id: user_info_delt
                    anchors.left: parent.left
                    anchors.leftMargin: 18
                    nick: _nick
                    head: _head
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
        itemClicked(user_name)
    }
}
