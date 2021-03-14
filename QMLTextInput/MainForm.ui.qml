import QtQuick 2.7  // 导入库

Rectangle {  // 根对象，每个qml文档有且只有一个根对象

    width: 360
    height: 360
    color: "lightgray"


    LineEdit {
        id: lE1
        x: 25; y: 25
        focus: true
        label: "学号"
        text: focus ? "" : "请输入内容..."
        KeyNavigation.tab: lE2
    }

    LineEdit {
        id: lE2
        x: 25; y: 60
        focus: false
        label: "姓名"
        text: focus ? "" : "请输入内容..."
        KeyNavigation.tab: lE1
    }

}
