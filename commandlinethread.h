#ifndef COMMANDLINETHREAD_H
#define COMMANDLINETHREAD_H

#include <QThread>
#include "config.h"
#include "ffmpeg.h"
#include "cmdutils.h"

class CommandLineThread : public QThread
{
    Q_OBJECT
public:
    static CommandLineThread* getInstance();
    CommandLineThread();

    //To execute command line
    void executeCommandLine(QString cmd);

private:
    void run() override;

    QString m_cmd;
};

#endif // COMMANDLINETHREAD_H
