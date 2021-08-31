import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    TIcon{
        width: 100
        height: 100
        source: "\uf004"
    }
    TIcon{
        x:200
        y:200
        width: 100
        height: 100
        source: "qrc:/svg/close.svg"
    }
}
