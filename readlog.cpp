#include "readlog.h"

ReadLog::ReadLog()
{
//    cout << "ReadLog constructor; Thread id = " << this_thread::get_id() << "\n";
}

void ReadLog::read()
{
//    this_thread::sleep_for(chrono::seconds(5));
    logFile = new QFile(QString::fromStdString(getPath()));
    logInfo = new QFileInfo(*logFile);
    if(logFile->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        cout << "Successfully opened the file.\n";
        if(logInfo->suffix() == "log")
        {
            cout << "Your file is a valid log file. Now trying to read logs ...\n";
            readFunction();
        }
        else
            cout << "Your file isn't in <log> format\n";
    }
    else
        cout << "Can't open file\n";
}

string ReadLog::getPath()
{
    glv::mutGetInput.lock();
    cout << "Enter a valid log path (e.g. /home/access.log): " ;
    string logPath;
    cin >> logPath;
    glv::mutGetInput.unlock();
    return logPath;
}

void ReadLog::readFunction()
{
    while (true)
    {
        if(logFile->atEnd())
        {
            logFile->seek(0);
            this_thread::sleep_for(chrono::seconds(10));
        }
        QByteArray log = logFile->readLine();
        glv::mutReady.lock();
        glv::logQueue.push(log);
        if(!glv::logQueue.empty())
        {
            glv::mutReady.unlock();
            glv::condVar.notify_one();
        }
        else
            glv::mutReady.unlock();
    }
}
