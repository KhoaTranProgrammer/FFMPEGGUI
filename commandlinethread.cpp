#include "commandlinethread.h"

static CommandLineThread *myCmd = NULL;

CommandLineThread* CommandLineThread::getInstance()
{
    if(!myCmd){
        myCmd = new CommandLineThread();
    }

    return myCmd;
}

CommandLineThread::CommandLineThread()
{

}

void CommandLineThread::executeCommandLine(QString cmd)
{
    m_cmd = cmd;
    CommandLineThread::getInstance()->start();
}

void CommandLineThread::run()
{
    int i = 0;

    QStringList cmd_list;
    QByteArray array;

    cmd_list = m_cmd.split(' ', QString::SkipEmptyParts);

    int margc = cmd_list.length() + 1;
    char** margv;

    margv = (char**)malloc(sizeof(char**) * margc);

    *(margv + 0) = "ffmpeg";
    for(int i = 0; i < cmd_list.length(); i++){
        array = cmd_list.at(i).toLocal8Bit();
        char* option_str = (char*)malloc(sizeof(char) * array.size());
        strcpy(option_str, array.data());
        *(margv + 1 + i) = option_str;
    }

    mymain(margc, margv);
}
