#ifndef FFMPEG_H
#define FFMPEG_H

#include <QObject>
#include <QVector>

#ifdef __cplusplus
extern "C" {
#endif

#include "config.h"
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavutil/ffversion.h"
#include "libavutil/version.h"

const char program_name[] = "ffmpeg";
const int program_birth_year = 2000;

enum show_muxdemuxers {
    SHOW_DEFAULT,
    SHOW_DEMUXERS,
    SHOW_MUXERS,
};

int compare_codec_desc(const void *a, const void *b);
static char get_media_type_char(enum AVMediaType type);
#ifdef __cplusplus
}
#endif

class FFMpeg : public QObject
{
    Q_OBJECT
public:
    static FFMpeg* getInstance();
    explicit FFMpeg();

public slots:
    //For get general information
    QString getProgramInfo();
    QString getCompilerInfo();
    QString getConfigurationInfo();

    //For access Codecs
    int getCodecsCount();
    QString getCodecsNameAt(int i);
    QString getCodecsLongNameAt(int i);
    QString getCodecsType(int i);
    QString getCodecsDecoder(int i);
    QString getCodecsEncoder(int i);
    QString getCodecsIntraOnly(int i);
    QString getCodecsLossy(int i);
    QString getCodecsLossless(int i);

    //For access Decoders
    int getDecodersCount();
    QString getDecoderNameAt(int i);
    QString getDecoderLongNameAt(int i);
    QString getDecoderType(int i);
    QString getDecoderFrameThreads(int i);
    QString getDecoderSliceThreads(int i);
    QString getDecoderExperimental(int i);
    QString getDecoderDrawHorizBand(int i);
    QString getDecoderDr1(int i);

    //For access Encoders
    int getEncodersCount();
    QString getEncoderNameAt(int i);
    QString getEncoderLongNameAt(int i);
    QString getEncoderType(int i);
    QString getEncoderFrameThreads(int i);
    QString getEncoderSliceThreads(int i);
    QString getEncoderExperimental(int i);
    QString getEncoderDrawHorizBand(int i);
    QString getEncoderDr1(int i);

    //For access Demuxers
    int getDemuxersCount();
    QString getDemuxersNameAt(int i);
    QString getDemuxersLongNameAt(int i);

    //For access Muxers
    int getMuxersCount();
    QString getMuxersNameAt(int i);
    QString getMuxersLongNameAt(int i);

private slots:
    void getGeneralInfo();
    unsigned get_codecs_sorted(const AVCodecDescriptor ***rcodecs);
    AVCodec *next_codec_for_id(enum AVCodecID id, AVCodec *prev, int encoder);
    void get_decodecs_list();
    void get_encodecs_list();
    void get_muxers_list();
    void get_demuxers_list();
    void add_muxerToList(AVOutputFormat *ofmt);
    void add_demuxerToList(AVInputFormat *ifmt);

private:
    //General Information
    QString m_programInfo;
    QString m_compilerInfo;
    QString m_configurationInfo;

    //List of Decoders
    QVector<AVCodec*> m_listOfDecoders;

    //List of Encoders
    QVector<AVCodec*> m_listOfEncoders;

    //List of Codecs
    const AVCodecDescriptor **m_listOfCodecs;
    unsigned m_nbCodecs;

    //List of Formats
    QVector<AVInputFormat*> m_listOfDemuxers;
    QVector<AVOutputFormat*> m_listOfMuxers;

};

#endif // FFMPEG_H
