import QtQuick 2.0

Item {
    id: wxSearchBar
    property alias searchContent: search_input.text

    signal searchTextChanged(string search_text)

    property string color_back: "#26292e"
    property string color_text: "#7e7f82"
    property string image_source : "res/main_source.png"

    width: 244
    height: 30
    Rectangle{
        anchors.fill: parent
        color: color_back
        radius: 3

        Row{
            id: row
            anchors.fill: parent
            UtilClipImage{
                id: img_search
                width: 30
                height: 30
                pos_x: -60
                pos_y: -432
                source_image: image_source
            }
            TextInput{
                id: search_input
                height: 30
                width: parent.width - img_search.width
                color: "#fff"
                anchors.top: parent.top
                anchors.topMargin: 6
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 15
                selectionColor: "#5c59e2"
                horizontalAlignment: Text.AlignLeft
                onTextChanged: searchTextChanged(text)
                selectByMouse: true
                cursorVisible: true
                focus: true
            }
        }
    }
}
