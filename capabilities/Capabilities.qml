import QtQuick 2.0
import "../js/CapabilitiesData.js" as Data

Item {
    id: root

    property string selectedCapability: ""

    ListModel {
        id: id_listOfCapabilities
    }

    Component.onCompleted: {
        for(var i = 0; i < Data.listOfCapabilities.length; i++){
            addCapability(Data.listOfCapabilities[i])
        }
    }

    Component {
        id: id_displayDelegate

        Item {
            width: root.width * 0.15
            height: root.height * 0.1
            Rectangle {
                id: id_button
                property string newCapability: root.selectedCapability

                anchors {
                    fill: parent
                    margins: parent.height * 0.05
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
                        root.selectedCapability = id_text.text
                    }
                }

                onNewCapabilityChanged: {
                    if(newCapability == id_text.text) {
                        id_button.color = "#80CBC4"
                    }else {
                        id_button.color = "#616161"
                    }
                }
            }
        }
    }

    Row {
        anchors.fill: parent
        Repeater {
            model: id_listOfCapabilities
            delegate: id_displayDelegate
        }
    }

    Rectangle {
        id: id_detail
        anchors {
            right: root.right
            left: root.left
            bottom: root.bottom
        }
        height: root.height * 0.9
        color: "transparent"
    }

    Loader {
        id: id_loader
    }

    function addCapability(name)
    {
        id_listOfCapabilities.append({"name": name})
    }

    onSelectedCapabilityChanged: {
        id_loader.source = ""

        if(root.selectedCapability == Data.str_Decoders){
            id_loader.source = "DisplayDecoders.qml"
        }else if(root.selectedCapability == Data.str_Encoders){
            id_loader.source = "DisplayEncoders.qml"
        }else if(root.selectedCapability == Data.str_Codecs){
            id_loader.source = "DisplayCodecs.qml"
        }else if(root.selectedCapability == Data.str_Demuxers){
            id_loader.source = "DisplayDemuxers.qml"
        }else if(root.selectedCapability == Data.str_Muxers){
            id_loader.source = "DisplayMuxers.qml"
        }else{

        }

        if(id_loader.source != ""){
            var scene = null
            scene = id_loader.item
            scene.parent = root
            scene.anchors.fill = id_detail
            scene.ffmpeg = ffmpeg
            scene.init()
        }
    }
}
