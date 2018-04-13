import QtQuick 2.0
import "../"
import "../template/"

FormatTemplate {
    function init(){
        for(var i = 0; i < ffmpeg.getDemuxersCount(); i++){
            addItem(
                "D", "",
                ffmpeg.getDemuxersNameAt(i),
                ffmpeg.getDemuxersLongNameAt(i))
        }
    }
}
