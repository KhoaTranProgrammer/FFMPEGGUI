import QtQuick 2.0
import "js/OptionsData.js" as Data

Item {
    id: root

    property string selectedOption: ""

    ListModel {
        id: id_listOfOptions
    }

    Component.onCompleted: {
        for(var i = 0; i < Data.listOfOptions.length; i+=3){
            addItem(Data.listOfOptions[i], Data.listOfOptions[i+1], Data.listOfOptions[i+2])
        }
    }

    Component {
        id: id_displayDelegate

        Item {
            width: root.height * 0.9
            height: root.height

            Rectangle {
                id: id_bg

                property string newOption: root.selectedOption

                anchors.fill: parent
                anchors.margins: parent.height * 0.01
                color: "#80CBC4"
                radius: height * 0.15

                Image {
                    id: id_image
                    anchors {
                        top: parent.top
                        left: parent.left
                        right: parent.right
                        margins: parent.height * 0.08
                    }
                    height: width
                    smooth: true
                    source: "images/" + unselected
                }

                Text {
                    id: id_text
                    anchors {
                        bottom: parent.bottom
                        horizontalCenter: parent.horizontalCenter
                    }

                    text: text1
                    font.pixelSize: parent.height / 5
                    color: "black"
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        root.selectedOption = id_text.text
                    }
                }

                onNewOptionChanged: {
                    if(newOption == id_text.text) {
                        id_image.source = "images/" + selected
                    }else {
                        id_image.source = "images/" + unselected
                    }
                }
            }
        }
    }

    Row {
        anchors.fill: parent
        Repeater {
            model: id_listOfOptions
            delegate: id_displayDelegate
        }
    }

    Loader {
        id: id_loader
    }

    function addItem(text, image1, image2)
    {
        id_listOfOptions.append({"text1": text,
                                "unselected": image1,
                                "selected": image2
                                })
    }

    function loadOption()
    {
        if(root.selectedOption == Data.codecs) {
            return "capabilities/" + "Capabilities.qml"
        }else if(root.selectedOption == Data.infor) {
            return "Information.qml"
        }else{
            return "";
        }
    }
}
