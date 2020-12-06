import QtQuick 2.0

Rectangle {  // 将Rectangle自定义成按钮
    id: btn
    width: 100
    height: 62
    color: "teal"
    border.color: "aqua"
    border.width: 3

    Text {
        id: label
        anchors.centerIn: parent
        font.pointSize: 16
        text: "开始"
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            label.text = "按钮已按下！"
            label.font.pointSize = 9
            btn.color = "aqua"
            btn.border.color = "teal"
        }
    }
}
