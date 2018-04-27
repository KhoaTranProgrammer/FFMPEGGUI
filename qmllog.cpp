#include "qmllog.h"
#include <QDebug>

QMLLog::QMLLog()
{
    QObject::connect(CustomLog::getInstance(), SIGNAL(newLog(QString)), this, SLOT(newLogCome(QString)));
}

void QMLLog::newLogCome(QString log)
{
    qDebug() << log;
}
