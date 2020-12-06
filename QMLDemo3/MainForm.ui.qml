import QtQuick 2.7

Rectangle {
    Image {
        x: 20
        y: 20
        source: "images/sweet_2.jpg"
        fillMode: Image.PreserveAspectCrop  // 设置图片填充模式
        clip: true  // 避免所要渲染的图片超出元素范围
    }
}
