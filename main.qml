import QtQuick 2.3

Rectangle {
    id: root
    anchors.fill: parent
    color: "#90CAF9"

    QtObject {
        id: priv
        property var str_Codecs: "Codecs"
        property var str_Decoders: "Decoders"
        property var str_Encoders: "Encoders"
        property var listOfOption:
            [
                str_Codecs,
                str_Decoders,
                str_Encoders
            ]
    }

    Options{
        id: id_options
        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
        }
        height: parent.height * 0.1

        Component.onCompleted: {
            for(var i = 0; i < priv.listOfOption.length; i++){
                id_options.addItem(priv.listOfOption[i])
            }
        }

        onSelectedOptionChanged: {
            id_loader.source = ""

            if(id_options.selectedOption == priv.str_Decoders){
                id_loader.source = "Display/" + "DisplayDecoders.qml"
            }else if(id_options.selectedOption == priv.str_Encoders){
                id_loader.source = "Display/" + "DisplayEncoders.qml"
            }else if(id_options.selectedOption == priv.str_Codecs){
                id_loader.source = "Display/" + "DisplayCodecs.qml"
            }else{

            }

            if(id_loader.source != ""){
                var scene = null
                scene = id_loader.item
                scene.parent = root
                scene.anchors.fill = id_display
                scene.ffmpeg = ffmpeg
                scene.init()
            }
        }
    }

    Rectangle {
        id: id_display
        anchors {
            top: id_options.bottom
            right: parent.right
            left: parent.left
            bottom: parent.bottom
        }
        color: "transparent"
    }

    Loader {
        id: id_loader
    }
}
