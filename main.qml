import QtQuick 2.3

Rectangle {
    id: root
    anchors.fill: parent
    color: "#78909C"

    Options {
        id: id_options
        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
        }
        height: parent.height * 0.15

        onSelectedOptionChanged: {
            id_loader.source = ""
            id_loader.source = id_options.loadOption()
            var scene = null
            scene = id_loader.item
            scene.parent = root
            scene.anchors.fill = id_display
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
