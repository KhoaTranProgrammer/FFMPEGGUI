#include "customlog.h"

static CustomLog *myCustomLog = NULL;

static void av_log_custome_callback(void* ptr, int level, const char* fmt, va_list vl)
{
    CustomLog::getInstance()->processCallback(ptr, level, fmt, vl);
}

CustomLog* CustomLog::getInstance()
{
    if(!myCustomLog){
        myCustomLog = new CustomLog();
    }

    return myCustomLog;
}

CustomLog::CustomLog()
{

}

void CustomLog::setupCallback()
{
    av_log_set_callback(av_log_custome_callback);
}

void CustomLog::processCallback(void* ptr, int level, const char* fmt, va_list vl)
{
    emit newLog("newLog has come");
}
