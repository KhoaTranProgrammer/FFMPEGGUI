import QtQuick 2.0

Rectangle {
    id: root
    color: "transparent"

    Component.onCompleted: {
        id_list.append({"name": ffmpeg.getProgramInfo()})
        id_list.append({"name": ffmpeg.getCompilerInfo()})
        id_list.append({"name": ffmpeg.getConfigurationInfo()})
    }

    ListModel {
        id: id_list
    }

    Component {
        id: id_displayDelegate

        Text {
            width: root.width

            text: name
            font.pixelSize: 30
            color: "white"
            wrapMode: Text.WordWrap

            Rectangle {
                anchors.fill: parent
                color: "#80CBC4"
                opacity: 0.3
                z: -1
            }
        }
    }

    Column {
        anchors.fill: parent
        spacing: 10
        Repeater {
            model: id_list
            delegate: id_displayDelegate
        }
    }
}
