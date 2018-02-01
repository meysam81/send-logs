#ifndef READLOG_H
#define READLOG_H
#include "GlobalVariable.h"
#include <QFile>
#include <QFileInfo>
class ReadLog
{
private:
    QFile* logFile;
    QFileInfo* logInfo;
    //=================================
    string getPath();
    void readFunction();
public:
    ReadLog();
    void read();
};
#endif // READLOG_H
