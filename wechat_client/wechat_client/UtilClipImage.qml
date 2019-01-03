import QtQuick 2.0

/* 自定义贴图的组件，设置好原图片和剪裁坐标，大小即可 */

Item {
    id: utilClipImage
    property alias pos_x: img.x
    property alias pos_y: img.y
    property alias source_image: img.source

    Rectangle {
        id: rect
        color:"transparent";
        clip:true;
        anchors.fill: parent
        Image {
            id: img
        }
    }
}
