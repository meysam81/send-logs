#ifndef GLOBALVARIABLE_H
#define GLOBALVARIABLE_H
#include <iostream>
using namespace std;
#include <condition_variable>
#include <mutex>
#include <queue>
#include <QCoreApplication>
#include "readlog.h"
#include "sendlog.h"
#include <thread>
#include <vector>
#include <algorithm>
#include <QDateTime>
//=================================Declaration=====================================
struct glv
{
    static mutex mutReady;
    static mutex mutGetInput;
    static condition_variable condVar;
    static queue<QByteArray> logQueue;
    static short eps;
};
struct destination
{
    static string ipAddress;
    static quint16 port;
    static mutex desMut;
};
#endif // GLOBALVARIABLE_H
