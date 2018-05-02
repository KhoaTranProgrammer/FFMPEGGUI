import QtQuick 2.0
import QMLLog 1.0

Item {
    id: root

    property int numberOfLine: 0

    Text {
        id: id_textFFmpeg
        anchors {
            top: root.top
            left: root.left
        }

        text: "./ffmpeg "
        font.pixelSize: 25
        color: "white"
        wrapMode: Text.WordWrap
    }

    TextEdit {
        id: id_command
        anchors {
            top: root.top
            right: root.right
            left: id_textFFmpeg.right
        }

        text: ""
        font.pointSize: 20
        color: "white"
        focus: true
    }

    Rectangle {
        anchors {
            top: root.top
            left: root.left
            right: root.right
            bottom: id_command.bottom
        }

        color: "black"
        opacity: 0.3
        z: -1
    }

    Rectangle {
        anchors {
            top: root.top
            right: root.right
            bottom: id_command.bottom
        }
        width: root.width * 0.07

        color: "blue"

        MouseArea{
            anchors.fill: parent
            onClicked: {
                ffmpeg.executeCommandLine(id_command.text)
            }
        }
    }

    QMLLog {
        onNewLogCome: {
            id_textOutputLog.text += log
            numberOfLine++
        }
    }

    Flickable {
        id: id_flickarea
        anchors {
            left: parent.left
            right: parent.right
            top: id_command.bottom
            bottom: parent.bottom
        }

        contentHeight: numberOfLine * 20
        clip: true

        Text {
            id: id_textOutputLog
            anchors.fill: parent

            text: ""
            font.pixelSize: 15
            color: "white"
            wrapMode: Text.WordWrap
        }
    }
}
