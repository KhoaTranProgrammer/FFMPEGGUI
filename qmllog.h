#ifndef QMLLOG_H
#define QMLLOG_H

#include <QObject>
#include "customlog.h"

class QMLLog : public QObject
{
    Q_OBJECT
public:
    QMLLog();

public slots:
    void newLogCome(QString log);
};

#endif // QMLLOG_H
