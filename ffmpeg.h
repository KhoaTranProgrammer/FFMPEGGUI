#ifndef FFMPEG_H
#define FFMPEG_H

#include <QObject>
#include <QVector>

#ifdef __cplusplus
extern "C" {
#endif

#include "config.h"
#include "libavcodec/avcodec.h"

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

private slots:
    unsigned get_codecs_sorted(const AVCodecDescriptor ***rcodecs);
    AVCodec *next_codec_for_id(enum AVCodecID id, AVCodec *prev, int encoder);
    void get_decodecs_list();
    void get_encodecs_list();

private:
    QVector<AVCodec*> m_listOfDecoders;
    QVector<AVCodec*> m_listOfEncoders;
    const AVCodecDescriptor **m_listOfCodecs;
    unsigned m_nbCodecs;
};

#endif // FFMPEG_H
