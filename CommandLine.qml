import QtQuick 2.0
import QtQuick.Controls 1.4
import QMLLog 1.0

Item {
    id: root

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
                id_textOutputLog.text = ""
                ffmpeg.executeCommandLine(id_command.text)
            }
        }
    }

    QMLLog {
        onNewLogCome: {
            id_textOutputLog.text += log
            id_textOutputLog.cursorPosition = id_textOutputLog.text.length
        }
    }

    TextArea {
        id: id_textOutputLog
        anchors {
            left: parent.left
            right: parent.right
            top: id_command.bottom
            bottom: parent.bottom
        }

        readOnly: true
        text: ""
        font.family: "Courier New"
        font.pixelSize: 15
        textColor: "black"
        wrapMode: Text.WordWrap
    }
}
