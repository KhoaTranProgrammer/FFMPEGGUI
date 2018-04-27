#include "qmllog.h"
#include <QDebug>

QMLLog::QMLLog()
{
    QObject::connect(CustomLog::getInstance(), SIGNAL(newLog(QString)), this, SIGNAL(newLogCome(QString)));
}
