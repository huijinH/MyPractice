import QtQuick 2.7

Rectangle {

    Text {  // 普通文本
        x: 60
        y: 100
        color: "green"
        font.family: "Helvetica"
        font.pointSize: 24
        text: "Hello Qt Quick!"
    }

    Text {  // 富文本
        x: 60
        y: 140
        color: "green"
        font.family: "Helvetica"
        font.pointSize: 24
        text: "<b>Hello</b> <i>Qt Quick!</i>"
    }

    Text {  // 带样式的文本
        x: 60
        y: 180
        color: "green"
        font.family: "Helvetica"
        font.pointSize: 24
        style: Text.Outline; styleColor: "blue"
        text: "Hello Qt Quick!"
    }

    Text {  // 带省略的文本
        width: 200
        color: "green"
        font.family: "Helvetica"
        font.pointSize: 24
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignTop
        elide: Text.ElideRight  // 设置省略，如果没有设置Text的width，此属性将不起作用
        text: "Hello Qt Quick!"
    }

    Text {  // 换行文本
        width: 200
        y: 30
        color: "green"
        font.family: "Helvetica"
        font.pointSize: 24
        horizontalAlignment: Text.AlignLeft
        wrapMode: Text.WrapAnywhere  // 到达边界就换行，还可设置为Text.WordWrap只在单词边界换行
        text: "Hello Qt Quick!"
    }

}
