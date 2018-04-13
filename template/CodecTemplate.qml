import QtQuick 2.0
import "../"

Item {
    id: root

    property QtObject ffmpeg

    ListModel {
        id: id_list
    }

    Component {
        id: id_displayDelegate

        Item {
            width: root.width
            height: root.height * 0.1

            Rectangle {
                id: id_number
                anchors {
                    left: parent.left
                    top: parent.top
                    bottom: parent.bottom
                    margins: root.height * 0.01
                }
                width: height
                color: "#616161"
                radius: width * 0.1

                Text {
                    anchors.centerIn: parent
                    text: (index + 1)
                    font.pixelSize: id_number.height / 2
                    color: "white"
                }
            }

            Row {
                id: id_detail
                anchors {
                    left: id_number.right
                    top: parent.top
                    bottom: parent.bottom
                    margins: root.height * 0.01
                }
                spacing: 2
                CustomText { height: parent.height * 0.8; text: one}
                CustomText { height: parent.height * 0.8; text: two }
                CustomText { height: parent.height * 0.8; text: three }
                CustomText { height: parent.height * 0.8; text: four }
                CustomText { height: parent.height * 0.8; text: five }
                CustomText { height: parent.height * 0.8; text: six }
            }

            Rectangle {
                id: id_codecText
                anchors {
                    left: id_detail.right
                    top: parent.top
                    bottom: parent.bottom
                    margins: root.height * 0.01
                }
                width: parent.width * 0.2
                color: "#616161"

                Text {
                    id: id_text
                    anchors.centerIn: parent
                    text: codecname
                    font.pixelSize: id_codecText.height / 2
                    color: "white"
                }
            }

            Rectangle {
                id: id_codecLongText
                anchors {
                    left: id_codecText.right
                    top: parent.top
                    bottom: parent.bottom
                    right: parent.right
                    margins: root.height * 0.01
                }
                color: "#616161"

                Text {
                    id: id_text2
                    anchors.centerIn: parent
                    text: codeclongname
                    font.pixelSize: id_codecLongText.height / 3
                    color: "white"
                }
            }
        }
    }

    Flickable {
        id: id_flickarea
        anchors.fill: parent
        contentHeight: id_list.count * root.height * 0.1
        clip: true

        Column {
            anchors.fill: parent
            Repeater {
                model: id_list
                delegate: id_displayDelegate
            }
        }
    }

    ScrollBar {
        scrollArea: id_flickarea
        width: id_flickarea.width * 0.02
        anchors.right: id_flickarea.right
        anchors.top: id_flickarea.top
        anchors.bottom: id_flickarea.bottom
    }

    function addItem(one, two, three, four, five, six, codecname, codeclongname)
    {
        id_list.append({"one": one,
                        "two": two,
                        "three": three,
                        "four": four,
                        "five": five,
                        "six": six,
                        "codecname": codecname,
                        "codeclongname": codeclongname})
    }
}
