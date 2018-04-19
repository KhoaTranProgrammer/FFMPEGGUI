#ifndef FILEINFORMATION_H
#define FILEINFORMATION_H

#include <QObject>

#ifdef __cplusplus
extern "C" {
#endif

#include "config.h"
#include "ffmpeg_c.h"
#include "cmdutils.h"
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavutil/avstring.h"
#include "libavutil/opt.h"

#ifdef __cplusplus
}
#endif

class FileInformation
{
public:
    FileInformation(AVFormatContext *fmt_ctx);

public slots:
    QStringList getMetadata();
    QStringList getGeneralData();
    int getStreamCount();
    QStringList getStreamData(int index);

private slots:
    QStringList getInternalMetadata(AVDictionary *m);

private:
    //File Context
    AVFormatContext *m_fmtCtx;
};

#endif // FILEINFORMATION_H
