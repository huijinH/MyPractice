import QtQuick 2.7  // 导入库

Rectangle {  // 根对象，每个qml文档有且只有一个根对象
    property alias mouseArea: mouseArea  // 属性别名，用于外部对象修改和访问QML文档中的子对象
    property alias textEdit: textEdit

    width: 360
    height: 360

    MouseArea {  // 子对象1 MouseArea
        id: mouseArea  // 对象标识符
        anchors.fill: parent  // 布局填满父对象
    }

    TextEdit {  // 子对象2 TextEdit
        id: textEdit
        text: qsTr("Enter some text...")
        verticalAlignment: Text.AlignVCenter
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 20  // 和上面两个都是布局作用
        Rectangle {  // 子对象2的子对象
            anchors.fill: parent
            anchors.margins: -10
            color: "transparent"
            border.width: 1
        }
    }
}
