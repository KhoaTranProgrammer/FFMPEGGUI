import QtQuick 2.0

Item {
    id: root

    property string selectedOption: ""

    ListModel {
        id: id_listOfOptions
    }

    Component {
        id: id_displayDelegate

        Item {
            width: root.width * 0.2
            height: root.height
            Rectangle {
                id: id_button
                property string newOption: root.selectedOption

                anchors {
                    fill: parent
                    margins: root.height * 0.1
                }
                color: "#616161"

                Text {
                    id: id_text
                    anchors.centerIn: parent
                    text: name
                    font.pixelSize: id_button.height / 2
                    color: "white"
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        root.selectedOption = id_text.text
                    }
                }

                onNewOptionChanged: {
                    if(newOption == id_text.text) {
                        id_button.color = "light blue"
                    }else {
                        id_button.color = "#616161"
                    }
                }
            }
        }
    }

    Flickable {
        anchors.fill: parent
        contentWidth: root.width + 100
        clip: true

        Row {
            anchors.fill: parent
            Repeater {
                model: id_listOfOptions
                delegate: id_displayDelegate
            }
        }
    }

    function addItem(name)
    {
        id_listOfOptions.append({"name": name})
    }
}
