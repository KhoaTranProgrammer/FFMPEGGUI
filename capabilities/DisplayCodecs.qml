import QtQuick 2.0
import "../"
import "../template/"

CodecTemplate {

    function init(){
        for(var i = 0; i < ffmpeg.getCodecsCount(); i++){
            addItem(
                ffmpeg.getCodecsDecoder(i),
                ffmpeg.getCodecsEncoder(i),
                ffmpeg.getCodecsType(i),
                ffmpeg.getCodecsIntraOnly(i),
                ffmpeg.getCodecsLossy(i),
                ffmpeg.getCodecsLossless(i),
                ffmpeg.getCodecsNameAt(i),
                ffmpeg.getCodecsLongNameAt(i))
        }
    }
}
