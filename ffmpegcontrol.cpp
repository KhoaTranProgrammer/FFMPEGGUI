#include "ffmpegcontrol.h"
#include <QDebug>
static FFMpegControl *myFFMpeg = NULL;

FFMpegControl* FFMpegControl::getInstance()
{
    if(!myFFMpeg){
        myFFMpeg = new FFMpegControl();
    }

    return myFFMpeg;
}

FFMpegControl::FFMpegControl()
{
    //Init custom log
    CustomLog::getInstance()->setupCallback();

    //Init avcodec
    avcodec_register_all();
    avfilter_register_all();
    av_register_all();
    avformat_network_init();

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

int FFMpegControl::executeCommandLine(QString cmd)
{
    CommandLineThread::getInstance()->executeCommandLine(cmd);
    return 0;
}

QString FFMpegControl::getProgramInfo()
{
    return m_programInfo;
}

QString FFMpegControl::getCompilerInfo()
{
    return m_compilerInfo;
}

QString FFMpegControl::getConfigurationInfo()
{
    return m_configurationInfo;
}

int FFMpegControl::getCodecsCount()
{
    return m_nbCodecs;
}

QString FFMpegControl::getCodecsNameAt(int i)
{
    return m_listOfCodecs[i]->name;
}

QString FFMpegControl::getCodecsLongNameAt(int i)
{
    return m_listOfCodecs[i]->long_name;
}

QString FFMpegControl::getCodecsType(int i)
{
    return (QString)get_media_type_char(m_listOfCodecs[i]->type);
}

QString FFMpegControl::getCodecsDecoder(int i)
{
    if(avcodec_find_decoder(m_listOfCodecs[i]->id)) return "D";
    return ".";
}

QString FFMpegControl::getCodecsEncoder(int i)
{
    if(avcodec_find_encoder(m_listOfCodecs[i]->id)) return "E";
    return ".";
}

QString FFMpegControl::getCodecsIntraOnly(int i)
{
    if(m_listOfCodecs[i]->props & AV_CODEC_PROP_INTRA_ONLY) return "I";
    return ".";
}

QString FFMpegControl::getCodecsLossy(int i)
{
    if(m_listOfCodecs[i]->props & AV_CODEC_PROP_LOSSY) return "L";
    return ".";
}

QString FFMpegControl::getCodecsLossless(int i)
{
    if(m_listOfCodecs[i]->props & AV_CODEC_PROP_LOSSLESS) return "S";
    return ".";
}

int FFMpegControl::getDecodersCount()
{
    return m_listOfDecoders.count();
}

QString FFMpegControl::getDecoderNameAt(int i)
{
    return m_listOfDecoders.at(i)->name;
}

QString FFMpegControl::getDecoderLongNameAt(int i)
{
    return m_listOfDecoders.at(i)->long_name;
}

QString FFMpegControl::getDecoderType(int i)
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

QString FFMpegControl::getDecoderFrameThreads(int i)
{
    if(m_listOfDecoders.at(i)->capabilities & AV_CODEC_CAP_FRAME_THREADS) return "F";
    return ".";
}

QString FFMpegControl::getDecoderSliceThreads(int i)
{
    if(m_listOfDecoders.at(i)->capabilities & AV_CODEC_CAP_SLICE_THREADS) return "S";
    return ".";
}

QString FFMpegControl::getDecoderExperimental(int i)
{
    if(m_listOfDecoders.at(i)->capabilities & AV_CODEC_CAP_EXPERIMENTAL) return "X";
    return ".";
}

QString FFMpegControl::getDecoderDrawHorizBand(int i)
{
    if(m_listOfDecoders.at(i)->capabilities & AV_CODEC_CAP_DRAW_HORIZ_BAND) return "B";
    return ".";
}

QString FFMpegControl::getDecoderDr1(int i)
{
    if(m_listOfDecoders.at(i)->capabilities & AV_CODEC_CAP_DR1) return "D";
    return ".";
}

int FFMpegControl::getEncodersCount()
{
    return m_listOfEncoders.count();
}

QString FFMpegControl::getEncoderNameAt(int i)
{
    return m_listOfEncoders.at(i)->name;
}

QString FFMpegControl::getEncoderLongNameAt(int i)
{
    return m_listOfEncoders.at(i)->long_name;
}

QString FFMpegControl::getEncoderType(int i)
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

QString FFMpegControl::getEncoderFrameThreads(int i)
{
    if(m_listOfEncoders.at(i)->capabilities & AV_CODEC_CAP_FRAME_THREADS) return "F";
    return ".";
}

QString FFMpegControl::getEncoderSliceThreads(int i)
{
    if(m_listOfEncoders.at(i)->capabilities & AV_CODEC_CAP_SLICE_THREADS) return "S";
    return ".";
}

QString FFMpegControl::getEncoderExperimental(int i)
{
    if(m_listOfEncoders.at(i)->capabilities & AV_CODEC_CAP_EXPERIMENTAL) return "X";
    return ".";
}

QString FFMpegControl::getEncoderDrawHorizBand(int i)
{
    if(m_listOfEncoders.at(i)->capabilities & AV_CODEC_CAP_DRAW_HORIZ_BAND) return "B";
    return ".";
}

QString FFMpegControl::getEncoderDr1(int i)
{
    if(m_listOfEncoders.at(i)->capabilities & AV_CODEC_CAP_DR1) return "D";
    return ".";
}

int FFMpegControl::getDemuxersCount()
{
    return m_listOfDemuxers.length();
}

QString FFMpegControl::getDemuxersNameAt(int i)
{
    return m_listOfDemuxers.at(i)->name;
}

QString FFMpegControl::getDemuxersLongNameAt(int i)
{
    return m_listOfDemuxers.at(i)->long_name;
}

int FFMpegControl::getMuxersCount()
{
    return m_listOfMuxers.length();
}

QString FFMpegControl::getMuxersNameAt(int i)
{
    return m_listOfMuxers.at(i)->name;
}

QString FFMpegControl::getMuxersLongNameAt(int i)
{
    return m_listOfMuxers.at(i)->long_name;
}

int FFMpegControl::findFormat(QString input)
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

QStringList FFMpegControl::getMetadata()
{
    QStringList nullStr;
    if(fileFormat) return fileFormat->getMetadata();
    return nullStr;
}

QStringList FFMpegControl::getGeneralData()
{
    QStringList nullStr;
    if(fileFormat) return fileFormat->getGeneralData();
    return nullStr;
}

int FFMpegControl::getStreamCount()
{
    return fileFormat->getStreamCount();
}

QStringList FFMpegControl::getStreamData(int index)
{
    QStringList nullStr;
    if(fileFormat) return fileFormat->getStreamData(index);
    return nullStr;
}

void FFMpegControl::getGeneralInfo()
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

QUrl FFMpegControl::getMovieLocation()
{
    const QStringList moviesLocation = QStandardPaths::standardLocations(QStandardPaths::MoviesLocation);
    return QUrl::fromLocalFile(moviesLocation.front());
}

unsigned FFMpegControl::get_codecs_sorted(const AVCodecDescriptor ***rcodecs)
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

AVCodec* FFMpegControl::next_codec_for_id(enum AVCodecID id, AVCodec *prev, int encoder)
{
    while ((prev = av_codec_next(prev))) {
        if (prev->id == id &&
            (encoder ? av_codec_is_encoder(prev) : av_codec_is_decoder(prev)))
            return prev;
    }
    return NULL;
}

void FFMpegControl::get_decodecs_list()
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

void FFMpegControl::get_encodecs_list()
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

void FFMpegControl::get_muxers_list()
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

void FFMpegControl::get_demuxers_list()
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

void FFMpegControl::add_muxerToList(AVOutputFormat *ofmt)
{
    for(int i = 0; i < m_listOfMuxers.length(); i++)
    {
        if(m_listOfMuxers.at(i)->name == ofmt->name) return;
    }
    m_listOfMuxers.append(ofmt);
}

void FFMpegControl::add_demuxerToList(AVInputFormat *ifmt)
{
    for(int i = 0; i < m_listOfDemuxers.length(); i++)
    {
        if(m_listOfDemuxers.at(i)->name == ifmt->name) return;
    }
    m_listOfDemuxers.append(ifmt);
}
