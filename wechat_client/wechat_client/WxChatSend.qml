import QtQuick 2.0
import QtQuick.Controls 2.4

Item {
    id: wxChatSend
    property alias sendContent: content.text

    property string color_chat_back: "#eeeeee"

    signal sendClicked(string _content)

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
                    //onTextChanged: print(content.text)
                    Keys.onPressed: {
                        if ((event.key === Qt.Key_Enter || event.key === Qt.Key_Return)
                                && (event.modifiers & Qt.ControlModifier)){
                            content.text += '\n'
                            content.cursorPosition = content.length
                            event.accepted = true
                        }
                        else if(event.key === Qt.Key_Enter || event.key === Qt.Key_Return){
                            sendClicked(content.text)
                            event.accepted = true
                        }
                    }
                }
            }
        }

        Rectangle {
            id: bottomBar
            height: 40
            width: parent.width
            anchors.top: inputBox.bottom
            color: color_chat_back

            Rectangle {
                id: btnSend
                width: 88
                height: 30
                anchors.rightMargin: 10
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                color: "#28B463"
                border.color: "green"
                border.width: 1
                radius: 5

                Text {
                    id: btnSendText
                    text: qsTr("发送")
                    anchors.centerIn: parent
                    color: "#fff"
                }

                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered: {
                        btnSend.color = "#58D68D"
                    }
                    onExited: {
                        btnSend.color = "#28B463"
                    }
                    onPressed: {
                        btnSend.color = "#1D8348"
                    }
                    onReleased: {
                        btnSend.color = "#28B463"
                    }
                    onClicked: {
                        sendClicked(content.text)
                    }
                }
            }
        }
    }
}
