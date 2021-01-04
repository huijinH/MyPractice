import QtQuick 2.0

Rectangle {
    width: 50; height: 50
    color: "teal"
    MouseArea {
        anchors.fill: parent
        drag.target: parent  // 拖拽属性设置
        drag.axis: Drag.XAxis  // 轴，拖动方向
        drag.minimumX: 0
        drag.maximumX: 360 - parent.width
        acceptedButtons: Qt.LeftButton|Qt.RightButton
        onClicked: {
            if (mouse.button == Qt.RightButton) {
                parent.color = "blue"
                parent.width -= 5
                parent.height -= 5
            } else if ((mouse.button == Qt.LeftButton) && (mouse.modifiers & Qt.ShiftModifier)) {
                parent.color = "teal"
                parent.width = 50
                parent.height = 50
            } else {
                parent.color = "green"
                parent.width += 5
                parent.height += 5
            }
        }
    }
}
