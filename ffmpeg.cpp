#include "ffmpeg.h"

static FFMpeg *myFFMpeg = NULL;

int compare_codec_desc(const void *a, const void *b)
{
    const AVCodecDescriptor * const *da = (const AVCodecDescriptor * const*)a;
    const AVCodecDescriptor * const *db = (const AVCodecDescriptor * const*)b;

    return (*da)->type != (*db)->type ? FFDIFFSIGN((*da)->type, (*db)->type) :
           strcmp((*da)->name, (*db)->name);
}

static char get_media_type_char(enum AVMediaType type)
{
    switch (type) {
        case AVMEDIA_TYPE_VIDEO:    return 'V';
        case AVMEDIA_TYPE_AUDIO:    return 'A';
        case AVMEDIA_TYPE_DATA:     return 'D';
        case AVMEDIA_TYPE_SUBTITLE: return 'S';
        case AVMEDIA_TYPE_ATTACHMENT:return 'T';
        default:                    return '?';
    }
}

FFMpeg* FFMpeg::getInstance()
{
    if(!myFFMpeg){
        myFFMpeg = new FFMpeg();
    }

    return myFFMpeg;
}

FFMpeg::FFMpeg()
{
    //Init avcodec
    avcodec_register_all();

    //Get codecs list
    m_nbCodecs = get_codecs_sorted(&m_listOfCodecs);

    //Get decoders
    get_decodecs_list();

    //Get encoders
    get_encodecs_list();
}

int FFMpeg::getCodecsCount()
{
    return m_nbCodecs;
}

QString FFMpeg::getCodecsNameAt(int i)
{
    return m_listOfCodecs[i]->name;
}

QString FFMpeg::getCodecsLongNameAt(int i)
{
    return m_listOfCodecs[i]->long_name;
}

QString FFMpeg::getCodecsType(int i)
{
    return (QString)get_media_type_char(m_listOfCodecs[i]->type);
}

QString FFMpeg::getCodecsDecoder(int i)
{
    if(avcodec_find_decoder(m_listOfCodecs[i]->id)) return "D";
    return ".";
}

QString FFMpeg::getCodecsEncoder(int i)
{
    if(avcodec_find_encoder(m_listOfCodecs[i]->id)) return "E";
    return ".";
}

QString FFMpeg::getCodecsIntraOnly(int i)
{
    if(m_listOfCodecs[i]->props & AV_CODEC_PROP_INTRA_ONLY) return "I";
    return ".";
}

QString FFMpeg::getCodecsLossy(int i)
{
    if(m_listOfCodecs[i]->props & AV_CODEC_PROP_LOSSY) return "L";
    return ".";
}

QString FFMpeg::getCodecsLossless(int i)
{
    if(m_listOfCodecs[i]->props & AV_CODEC_PROP_LOSSLESS) return "S";
    return ".";
}

int FFMpeg::getDecodersCount()
{
    return m_listOfDecoders.count();
}

QString FFMpeg::getDecoderNameAt(int i)
{
    return m_listOfDecoders.at(i)->name;
}

QString FFMpeg::getDecoderLongNameAt(int i)
{
    return m_listOfDecoders.at(i)->long_name;
}

QString FFMpeg::getDecoderType(int i)
{
    switch (m_listOfDecoders.at(i)->type) {
        case AVMEDIA_TYPE_VIDEO:        return "V";
        case AVMEDIA_TYPE_AUDIO:        return "A";
        case AVMEDIA_TYPE_DATA:         return "D";
        case AVMEDIA_TYPE_SUBTITLE:     return "S";
        case AVMEDIA_TYPE_ATTACHMENT:   return "T";
        default:                        return "?";
    }
}

QString FFMpeg::getDecoderFrameThreads(int i)
{
    if(m_listOfDecoders.at(i)->capabilities & AV_CODEC_CAP_FRAME_THREADS) return "F";
    return ".";
}

QString FFMpeg::getDecoderSliceThreads(int i)
{
    if(m_listOfDecoders.at(i)->capabilities & AV_CODEC_CAP_SLICE_THREADS) return "S";
    return ".";
}

QString FFMpeg::getDecoderExperimental(int i)
{
    if(m_listOfDecoders.at(i)->capabilities & AV_CODEC_CAP_EXPERIMENTAL) return "X";
    return ".";
}

QString FFMpeg::getDecoderDrawHorizBand(int i)
{
    if(m_listOfDecoders.at(i)->capabilities & AV_CODEC_CAP_DRAW_HORIZ_BAND) return "B";
    return ".";
}

QString FFMpeg::getDecoderDr1(int i)
{
    if(m_listOfDecoders.at(i)->capabilities & AV_CODEC_CAP_DR1) return "D";
    return ".";
}

int FFMpeg::getEncodersCount()
{
    return m_listOfEncoders.count();
}

QString FFMpeg::getEncoderNameAt(int i)
{
    return m_listOfEncoders.at(i)->name;
}

QString FFMpeg::getEncoderLongNameAt(int i)
{
    return m_listOfEncoders.at(i)->long_name;
}

QString FFMpeg::getEncoderType(int i)
{
    switch (m_listOfEncoders.at(i)->type) {
        case AVMEDIA_TYPE_VIDEO:        return "V";
        case AVMEDIA_TYPE_AUDIO:        return "A";
        case AVMEDIA_TYPE_DATA:         return "D";
        case AVMEDIA_TYPE_SUBTITLE:     return "S";
        case AVMEDIA_TYPE_ATTACHMENT:   return "T";
        default:                        return "?";
    }
}

QString FFMpeg::getEncoderFrameThreads(int i)
{
    if(m_listOfEncoders.at(i)->capabilities & AV_CODEC_CAP_FRAME_THREADS) return "F";
    return ".";
}

QString FFMpeg::getEncoderSliceThreads(int i)
{
    if(m_listOfEncoders.at(i)->capabilities & AV_CODEC_CAP_SLICE_THREADS) return "S";
    return ".";
}

QString FFMpeg::getEncoderExperimental(int i)
{
    if(m_listOfEncoders.at(i)->capabilities & AV_CODEC_CAP_EXPERIMENTAL) return "X";
    return ".";
}

QString FFMpeg::getEncoderDrawHorizBand(int i)
{
    if(m_listOfEncoders.at(i)->capabilities & AV_CODEC_CAP_DRAW_HORIZ_BAND) return "B";
    return ".";
}

QString FFMpeg::getEncoderDr1(int i)
{
    if(m_listOfEncoders.at(i)->capabilities & AV_CODEC_CAP_DR1) return "D";
    return ".";
}

unsigned FFMpeg::get_codecs_sorted(const AVCodecDescriptor ***rcodecs)
{
    const AVCodecDescriptor *desc = NULL;
    const AVCodecDescriptor **codecs;
    unsigned nb_codecs = 0, i = 0;

    while ((desc = avcodec_descriptor_next(desc)))
        nb_codecs++;
    if (!(codecs = (const AVCodecDescriptor **)av_calloc(nb_codecs, sizeof(*codecs)))) {
    }
    desc = NULL;
    while ((desc = avcodec_descriptor_next(desc)))
        codecs[i++] = desc;
    qsort(codecs, nb_codecs, sizeof(*codecs), compare_codec_desc);
    *rcodecs = codecs;
    return nb_codecs;
}

AVCodec* FFMpeg::next_codec_for_id(enum AVCodecID id, AVCodec *prev, int encoder)
{
    while ((prev = av_codec_next(prev))) {
        if (prev->id == id &&
            (encoder ? av_codec_is_encoder(prev) : av_codec_is_decoder(prev)))
            return prev;
    }
    return NULL;
}

void FFMpeg::get_decodecs_list()
{
    unsigned i;
    for (i = 0; i < m_nbCodecs; i++) {
        const AVCodecDescriptor *desc = m_listOfCodecs[i];
        AVCodec *codec = NULL;

        while ((codec = next_codec_for_id(desc->id, codec, 0))) {
            m_listOfDecoders.append(codec);
        }
    }
}

void FFMpeg::get_encodecs_list()
{
    unsigned i;
    for (i = 0; i < m_nbCodecs; i++) {
        const AVCodecDescriptor *desc = m_listOfCodecs[i];
        AVCodec *codec = NULL;

        while ((codec = next_codec_for_id(desc->id, codec, 1))) {
            m_listOfEncoders.append(codec);
        }
    }
}
