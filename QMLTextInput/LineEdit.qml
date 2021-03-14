import QtQuick 2.0

FocusScope {  // 置于其中的元素有效控制焦点
    property alias label: label.text
    property alias text: input.text

    Row {
        spacing: 5
        Text {
            id: label
            text: qsTr("标签")

        }

        Rectangle {  // 专为呈现输入框可视外观
            width: 100
            height: 25
            color: "white"
            border.color: "gray"
            TextInput {
                id: input
                anchors.fill: parent
                anchors.leftMargin: 7
                anchors.topMargin: 4
                focus: true
                text: qsTr("请输入内容...")
            }
        }
    }
}
