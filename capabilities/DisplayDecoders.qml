import QtQuick 2.0
import "../"
import "../template/"

CodecTemplate {

    function init(){
        for(var i = 0; i < ffmpeg.getDecodersCount(); i++){
            addItem(
                ffmpeg.getDecoderType(i),
                ffmpeg.getDecoderFrameThreads(i),
                ffmpeg.getDecoderSliceThreads(i),
                ffmpeg.getDecoderExperimental(i),
                ffmpeg.getDecoderDrawHorizBand(i),
                ffmpeg.getDecoderDr1(i),
                ffmpeg.getDecoderNameAt(i),
                ffmpeg.getDecoderLongNameAt(i))
        }
    }
}
