import QtQuick 2.0

Item {
    id: root

    property string source

    Rectangle {
        id: id_selectFile
        anchors {
            left: parent.left
            top: parent.top
            margins: root.height * 0.01
        }
        width: parent.width * 0.15
        height: parent.height * 0.1
        color: "black"

        Text {
            anchors.centerIn: parent
            text: "Open File:"
            font.pixelSize: id_selectFile.height / 2
            color: "white"
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                fileBrowser.folder = ffmpeg.getMovieLocation();
                fileBrowser.show()
            }
        }
    }

    Rectangle {
        anchors {
            left: id_selectFile.right
            right: parent.right
            top: parent.top
            margins: root.height * 0.01
        }
        height: parent.height * 0.1
        color: "black"

        Text {
            id: id_fileName
            anchors.centerIn: parent
            text: ""
            font.pixelSize: id_selectFile.height / 2
            color: "white"
        }
    }

    ListModel {
        id: id_list
    }

    Component {
        id: id_displayDelegate

        Item {
            width: root.width
            height: root.height * 0.1

            Rectangle {
                id: id_item
                anchors {
                    left: parent.left
                    top: parent.top
                    bottom: parent.bottom
                    margins: root.height * 0.01
                }
                width: parent.width * 0.2
                color: "#616161"

                Text {
                    id: id_text
                    anchors.centerIn: parent
                    text: item
                    font.pixelSize: id_item.height / 2
                    color: "white"
                }
            }

            Rectangle {
                id: id_content
                anchors {
                    left: id_item.right
                    top: parent.top
                    bottom: parent.bottom
                    right: parent.right
                    margins: root.height * 0.01
                }
                color: "#616161"

                Text {
                    id: id_text2
                    anchors.centerIn: parent
                    text: content
                    font.pixelSize: id_content.height / 3
                    color: "white"
                }
            }
        }
    }

    Flickable {
        id: id_flickarea
        anchors {
            top: id_selectFile.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
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

    FileBrowser {
        id: fileBrowser
        anchors {
            top: id_selectFile.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
        Component.onCompleted: fileSelected.connect(root.openFile)
    }

    function addItem(item, content)
    {
        id_list.append({"item": item, "content": content})
    }

    function openFile(path) {
        id_list.clear()
        root.source = path
        id_fileName.text = path
        if(!ffmpeg.findFormat(root.source)){
            var i
            var metastr = ffmpeg.getMetadata();
            for(i = 0; i < metastr.length; i += 2){
                addItem(metastr[i], metastr[i + 1])
            }
            var generalstr = ffmpeg.getGeneralData();
            for(i = 0; i < generalstr.length; i += 2){
                addItem(generalstr[i], generalstr[i + 1])
            }

            for(var j = 0; j < ffmpeg.getStreamCount(); j++){
                var streamstr = ffmpeg.getStreamData(j);
                for(i = 0; i < streamstr.length; i += 2){
                    addItem(streamstr[i], streamstr[i + 1])
                }
            }
        }
    }
}
