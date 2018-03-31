import QtQuick 2.0
import "../"

CodecTemplate {

    function init(){
        for(var i = 0; i < ffmpeg.getEncodersCount(); i++){
            addItem(ffmpeg.getEncoderType(i),
                    ffmpeg.getEncoderFrameThreads(i),
                    ffmpeg.getEncoderSliceThreads(i),
                    ffmpeg.getEncoderExperimental(i),
                    ffmpeg.getEncoderDrawHorizBand(i),
                    ffmpeg.getEncoderDr1(i),
                    ffmpeg.getEncoderNameAt(i),
                    ffmpeg.getEncoderLongNameAt(i))
        }
    }
}
