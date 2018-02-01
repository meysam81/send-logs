#ifndef SENDLOG_H
#define SENDLOG_H
#include "GlobalVariable.h"
#include <QTcpSocket>
#include <QHostAddress>
#include <QIODevice>
#include <thread>
class SendLog
{
private:
    QTcpSocket *sendSocket;
    queue<QByteArray> localQueue;
    thread *writeToLocal;
    thread *sendThread;
    //=============================================
    void establishConnection();
public:
    void getInputFromUser();
    SendLog();
    void send();
};


#endif // SENDLOG_H
