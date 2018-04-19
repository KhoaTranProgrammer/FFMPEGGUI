#include "fileinformation.h"

FileInformation::FileInformation(AVFormatContext *fmt_ctx)
{
    m_fmtCtx = fmt_ctx;
}

QStringList FileInformation::getMetadata()
{
    return getInternalMetadata(m_fmtCtx->metadata);
}

QStringList FileInformation::getGeneralData()
{
    QStringList list;
    AVFormatContext *ic = m_fmtCtx;

    //Get duration
    list.append("Duration");
    if (ic->duration != AV_NOPTS_VALUE) {
        int hours, mins, secs, us;
        int64_t duration = ic->duration + (ic->duration <= INT64_MAX - 5000 ? 5000 : 0);
        secs  = duration / AV_TIME_BASE;
        us    = duration % AV_TIME_BASE;
        mins  = secs / 60;
        secs %= 60;
        hours = mins / 60;
        mins %= 60;
        char duration_output[100];
        sprintf( duration_output, "%02d:%02d:%02d.%02d", hours, mins, secs, (100 * us) / AV_TIME_BASE);
        list.append(duration_output);
    } else {
        list.append("N/A");
    }

    //Get Start Time
    if (ic->start_time != AV_NOPTS_VALUE) {
        int secs, us;
        list.append("start");
        secs = llabs(ic->start_time / AV_TIME_BASE);
        us   = llabs(ic->start_time % AV_TIME_BASE);
        char starttime_output[100];
        sprintf(starttime_output, "%s%d.%06d",
                ic->start_time >= 0 ? "" : "-",
                secs,
                (int) av_rescale(us, 1000000, AV_TIME_BASE));
        list.append(starttime_output);
    }

    //Get Bitrate
    list.append("Bitrate");
    if (ic->bit_rate){
        char bitrate_output[100];
        sprintf(bitrate_output, "%lld kb/s", ic->bit_rate / 1000);
        list.append(bitrate_output);
    }else
        list.append("N/A");
    return list;
}

int FileInformation::getStreamCount()
{
    return m_fmtCtx->nb_streams;
}

QStringList FileInformation::getStreamData(int i)
{
    QStringList list;

    int index = 1;
    int is_output = 0;
    AVFormatContext *ic = m_fmtCtx;
    char buf[256];
    int flags = (is_output ? ic->oformat->flags : ic->iformat->flags);
    AVStream *st = ic->streams[i];
    AVDictionaryEntry *lang = av_dict_get(st->metadata, "language", NULL, 0);
    char *separator = (char *)ic->dump_separator;
    AVCodecContext *avctx;
    int ret;

    avctx = avcodec_alloc_context3(NULL);
    if (!avctx)
        return list;

    ret = avcodec_parameters_to_context(avctx, st->codecpar);
    if (ret < 0) {
        avcodec_free_context(&avctx);
        return list;
    }

    // Fields which are missing from AVCodecParameters need to be taken from the AVCodecContext
    avctx->properties = st->codec->properties;
    avctx->codec      = st->codec->codec;
    avctx->qmin       = st->codec->qmin;
    avctx->qmax       = st->codec->qmax;
    avctx->coded_width  = st->codec->coded_width;
    avctx->coded_height = st->codec->coded_height;

    if (separator)
        av_opt_set(avctx, "dump_separator", separator, 0);
    avcodec_string(buf, sizeof(buf), avctx, is_output);
    avcodec_free_context(&avctx);

    //av_log(NULL, AV_LOG_INFO, "    Stream #%d:%d", index, i);
    list.append("Stream");
    list.append(QString::number(i));
    /* the pid is an important information, so we display it */
    /* XXX: add a generic system */
    if (flags & AVFMT_SHOW_IDS){
        //av_log(NULL, AV_LOG_INFO, "[0x%x]", st->id);
        list.append("ID");
        list.append(QString::number(st->id));
    }
    if (lang){
        //av_log(NULL, AV_LOG_INFO, "(%s)", lang->value);
        list.append("Language");
        list.append(lang->value);
    }
    list.append("Info");
    list.append(buf);

    if (st->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
        int fps = st->avg_frame_rate.den && st->avg_frame_rate.num;
        int tbr = st->r_frame_rate.den && st->r_frame_rate.num;
        int tbn = st->time_base.den && st->time_base.num;
        int tbc = st->codec->time_base.den && st->codec->time_base.num;

        if (fps){
            list.append("FPS");
            list.append(QString::number(av_q2d(st->avg_frame_rate)));
        }
    }
    list += getInternalMetadata(st->metadata);
    return list;
}

QStringList FileInformation::getInternalMetadata(AVDictionary *m)
{
    QStringList list;

    if (m && !(av_dict_count(m) == 1 && av_dict_get(m, "language", NULL, 0))) {
        AVDictionaryEntry *tag = NULL;
        while ((tag = av_dict_get(m, "", tag, AV_DICT_IGNORE_SUFFIX))){
            if (strcmp("language", tag->key)) {
                const char *p = tag->value;
                list.append(tag->key);
                while (*p) {
                    char tmp[256];
                    size_t len = strcspn(p, "\x8\xa\xb\xc\xd");
                    av_strlcpy(tmp, p, FFMIN(sizeof(tmp), len+1));
                    list.append(tmp);
                    p += len;
                    if (*p) p++;
                }
            }
        }
    }
    return list;
}
