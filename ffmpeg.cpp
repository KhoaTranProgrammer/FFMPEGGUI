#include "ffmpeg.h"
#include <QDebug>
static FFMpeg *myFFMpeg = NULL;

FFMpeg* FFMpeg::getInstance()
{
    if(!myFFMpeg){
        myFFMpeg = new FFMpeg();
    }

    return myFFMpeg;
}

FFMpeg::FFMpeg()
{
    //Init custom log
    CustomLog::getInstance()->setupCallback();

    //Init avcodec
    avcodec_register_all();
    av_register_all();

    getGeneralInfo();

    //Get codecs list
    m_nbCodecs = get_codecs_sorted(&m_listOfCodecs);

    //Get decoders
    get_decodecs_list();

    //Get encoders
    get_encodecs_list();

    //Get formats
    get_muxers_list();
    get_demuxers_list();
}

int FFMpeg::executeCommandLine(QString cmd)
{
    QStringList cmd_list;
    QByteArray array;

    cmd_list = cmd.split(' ', QString::SkipEmptyParts);

    int margc = cmd_list.length() + 1;
    char** margv;

    margv = (char**)malloc(sizeof(char**) * margc);

    *(margv + 0) = "ffmpeg";
    for(int i = 0; i < cmd_list.length(); i++){
        array = cmd_list.at(i).toLocal8Bit();
        *(margv + 1 + i) = array.data();
    }

    return mymain(margc, margv);
}

QString FFMpeg::getProgramInfo()
{
    return m_programInfo;
}

QString FFMpeg::getCompilerInfo()
{
    return m_compilerInfo;
}

QString FFMpeg::getConfigurationInfo()
{
    return m_configurationInfo;
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

int FFMpeg::getDemuxersCount()
{
    return m_listOfDemuxers.length();
}

QString FFMpeg::getDemuxersNameAt(int i)
{
    return m_listOfDemuxers.at(i)->name;
}

QString FFMpeg::getDemuxersLongNameAt(int i)
{
    return m_listOfDemuxers.at(i)->long_name;
}

int FFMpeg::getMuxersCount()
{
    return m_listOfMuxers.length();
}

QString FFMpeg::getMuxersNameAt(int i)
{
    return m_listOfMuxers.at(i)->name;
}

QString FFMpeg::getMuxersLongNameAt(int i)
{
    return m_listOfMuxers.at(i)->long_name;
}

int FFMpeg::findFormat(QString input)
{
    input = input.right(input.length() - 8);
    if(fileFormat != NULL) delete fileFormat;
    if(fmt_ctx != NULL) avformat_close_input(&fmt_ctx);

    QByteArray array = input.toLocal8Bit();
    char* buffer = array.data();
    if (avformat_open_input(&fmt_ctx, buffer, NULL, NULL) < 0) {
        return 1; //Could not open source file
    }

    if (avformat_find_stream_info(fmt_ctx, NULL) < 0) {
        return 2; //Could not find stream information
    }

    fileFormat = new FileInformation(fmt_ctx);
    return 0;
}

QStringList FFMpeg::getMetadata()
{
    QStringList nullStr;
    if(fileFormat) return fileFormat->getMetadata();
    return nullStr;
}

QStringList FFMpeg::getGeneralData()
{
    QStringList nullStr;
    if(fileFormat) return fileFormat->getGeneralData();
    return nullStr;
}

int FFMpeg::getStreamCount()
{
    return fileFormat->getStreamCount();
}

QStringList FFMpeg::getStreamData(int index)
{
    QStringList nullStr;
    if(fileFormat) return fileFormat->getStreamData(index);
    return nullStr;
}

void FFMpeg::getGeneralInfo()
{
    m_programInfo = "ffmpeg version ";
    m_programInfo += FFMPEG_VERSION;
    m_programInfo += " Copyright (c) ";
    m_programInfo += "2000 - ";
    m_programInfo += QString::number(CONFIG_THIS_YEAR);
    m_programInfo += " the FFmpeg developers";

    m_compilerInfo = "built with ";
    m_compilerInfo += CC_IDENT;

    m_configurationInfo = "configuration: ";
    m_configurationInfo += FFMPEG_CONFIGURATION;
}

QUrl FFMpeg::getMovieLocation()
{
    const QStringList moviesLocation = QStandardPaths::standardLocations(QStandardPaths::MoviesLocation);
    return QUrl::fromLocalFile(moviesLocation.front());
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

int is_device(const AVClass *avclass)
{
    if (!avclass)
        return 0;
    return AV_IS_INPUT_DEVICE(avclass->category) || AV_IS_OUTPUT_DEVICE(avclass->category);
}

void FFMpeg::get_muxers_list()
{
    int device_only = 0;
    int muxdemuxers = SHOW_DEFAULT;
    AVOutputFormat *ofmt = NULL;
    const char *last_name;
    int is_dev;

    last_name = "000";
    for (;;) {
        int encode = 0;
        const char *name      = NULL;
        const char *long_name = NULL;

        if (muxdemuxers !=SHOW_DEMUXERS) {
            while ((ofmt = av_oformat_next(ofmt))) {
                is_dev = is_device(ofmt->priv_class);
                if (!is_dev && device_only)
                    continue;
                if ((!name || strcmp(ofmt->name, name) < 0) &&
                    strcmp(ofmt->name, last_name) > 0) {
                    name      = ofmt->name;
                    long_name = ofmt->long_name;
                    encode    = 1;
                    add_muxerToList(ofmt);
                }
            }
        }

        if (!name)
            break;
        last_name = name;
    }
}

void FFMpeg::get_demuxers_list()
{
    int device_only = 0;
    int muxdemuxers = SHOW_DEFAULT;
    AVInputFormat *ifmt  = NULL;
    const char *last_name;
    int is_dev;

    last_name = "000";
    for (;;) {
        int decode = 0;
        const char *name      = NULL;
        const char *long_name = NULL;

        if (muxdemuxers != SHOW_MUXERS) {
            while ((ifmt = av_iformat_next(ifmt))) {
                is_dev = is_device(ifmt->priv_class);
                if (!is_dev && device_only)
                    continue;
                if ((!name || strcmp(ifmt->name, name) < 0) &&
                    strcmp(ifmt->name, last_name) > 0) {
                    name      = ifmt->name;
                    long_name = ifmt->long_name;
                }
                if (name && strcmp(ifmt->name, name) == 0)
                {
                    decode = 1;
                    add_demuxerToList(ifmt);
                }
            }
        }

        if (!name)
            break;
        last_name = name;
    }
}

void FFMpeg::add_muxerToList(AVOutputFormat *ofmt)
{
    for(int i = 0; i < m_listOfMuxers.length(); i++)
    {
        if(m_listOfMuxers.at(i)->name == ofmt->name) return;
    }
    m_listOfMuxers.append(ofmt);
}

void FFMpeg::add_demuxerToList(AVInputFormat *ifmt)
{
    for(int i = 0; i < m_listOfDemuxers.length(); i++)
    {
        if(m_listOfDemuxers.at(i)->name == ifmt->name) return;
    }
    m_listOfDemuxers.append(ifmt);
}
