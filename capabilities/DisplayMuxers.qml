import QtQuick 2.0
import "../"
import "../template/"

FormatTemplate {
    function init(){
        for(var i = 0; i < ffmpeg.getMuxersCount(); i++){
            addItem(
                "", "E",
                ffmpeg.getMuxersNameAt(i),
                ffmpeg.getMuxersLongNameAt(i))
        }
    }
}
