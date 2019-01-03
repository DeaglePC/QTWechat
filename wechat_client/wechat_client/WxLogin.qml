import QtQuick 2.0

Item {
    id: wxLogin
    property alias hintMsgText: hint_msg.text

    // 各种提示类消息
    enum RET_MSG
    {
        LOGIN_SUCCESS = 10001,
        LOGIN_FAILED,
        HTTP_BAD_REQUEST = 20001,
        WX_INIT_SUCCESS = 30001,
        WX_GET_ALL_CONTACT_SUCCESS = 40001,
        WX_GET_ALL_CONTACT_FAILED,
        SYNC_FAILED = 50001
    }

    property alias qrcode: qrcode.source
    property alias hint_msg: hint_msg.text

    width: 300
    height: 350
    anchors.centerIn: parent

    Image {
        id: qrcode
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width
        height: parent.height - 50
        source: "res/loading.gif"
    }

    Text {
        id: hint_msg
        anchors.top: qrcode.bottom
        anchors.topMargin: 5
        anchors.horizontalCenter: parent.horizontalCenter
        text:qsTr("请用手机微信扫码登录！")
    }
}
