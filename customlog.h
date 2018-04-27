#ifndef CUSTOMLOG_H
#define CUSTOMLOG_H

#include <QObject>

#ifdef __cplusplus
  extern "C" {
#endif

#include "config.h"
#include "libavutil/log.h"
#include "libavutil/avstring.h"
#include "libavutil/bprint.h"

#ifdef __cplusplus
}
#endif

class CustomLog : public QObject
{
    Q_OBJECT

public:
    CustomLog();
    static CustomLog* getInstance();
    void setupCallback();
    void processCallback(void* ptr, int level, const char* fmt, va_list vl);

signals:
    void newLog(QString log);

private:
    void colored_fputs(int level, int tint, const char *str);
};

#endif // CUSTOMLOG_H
