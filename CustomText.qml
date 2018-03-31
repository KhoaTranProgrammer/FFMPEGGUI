import QtQuick 2.0

Rectangle {
    id: root

    property string text: ""

    color: "#616161"
    width: height
    anchors.verticalCenter: parent.verticalCenter

    Text {
        anchors.centerIn: parent
        text: root.text
        font.pixelSize: root.height / 2
        color: "white"
    }

    Component.onCompleted: {
        if(text == "V") {
            root.color = "green";
        }else if(text == "A"){
            root.color = "red";
        }else{
            root.color = "#616161";
        }
    }
}
