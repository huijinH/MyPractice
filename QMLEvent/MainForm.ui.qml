import QtQuick 2.7  // 导入库

Rectangle {  // 根对象，每个qml文档有且只有一个根对象
    //property alias mouseArea: mouseArea  // 属性别名，用于外部对象修改和访问QML文档中的子对象

    width: 360
    height: 360

    //MouseArea {  // 子对象1 MouseArea
    //    id: mouseArea  // 对象标识符
    //    anchors.fill: parent  // 布局填满父对象
    //}

    Rect {
        x: 25; y: 25
        opacity: (360.0-x)/360  // 透明度设置
    }
}
