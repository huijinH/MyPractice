import QtQuick 2.7

Rectangle {
    property alias mouseArea: mouseArea
    property alias topRect: topRect

    width: 360
    height: 360

    MouseArea {
        id: mouseArea
        anchors.fill: parent
    }

    Rectangle {
        rotation: 45  // 旋转45°
        x: 40
        y: 60  // 坐标
        width: 100
        height: 100
        color: "red"
    }

    Rectangle {
        id: topRect
        opacity: 0.6  // 透明度60%
        scale: 0.8  // 比例为原尺寸的80%
        x: 135
        y: 60
        width: 100
        height: 100
        radius: 8
        gradient: Gradient {  // 垂直方向渐变填充矩形
            GradientStop { position: 0.0; color: "aqua" }
            GradientStop { position: 1.0; color: "teal" }
        }
        border { width: 3; color: "blue" }
    }
}
