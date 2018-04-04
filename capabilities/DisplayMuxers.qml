import QtQuick 2.0
import "../"

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
