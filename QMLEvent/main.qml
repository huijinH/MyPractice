import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    width: 360
    height: 360
    visible: true
    title: qsTr("Hello World")

    MainForm {       // 子对象
        anchors.fill: parent
        //mouseArea.onClicked: {
            //console.log(qsTr('Clicked on background. Text: "' + textEdit.text + '"'))
        //}
    }

}
