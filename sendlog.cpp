#include "sendlog.h"

SendLog::SendLog()
{
    sendSocket = new QTcpSocket();
}

void SendLog::getInputFromUser()
{
    glv::mutGetInput.lock();
    if(destination::ipAddress == "")
    {
        cout << "Enter a valid IP address (e.g. 127.0.0.1): ";
        cin >> destination::ipAddress;
    }
    if(destination::port == 0)
    {
        cout << "Enter a valid port (e.g. 10000): ";
        cin >> destination::port;
    }
    if(glv::eps == 0)
    {
        cout << "Enter eps: ";
        cin >> glv::eps;
    }
    glv::mutGetInput.unlock();
}

void SendLog::establishConnection()
{
    sendSocket = new QTcpSocket();
    sendSocket->connectToHost(QString::fromStdString(destination::ipAddress), destination::port);
    sendSocket->waitForConnected();
}

void SendLog::send()
{
    unique_lock<mutex> lock(glv::mutReady);
    glv::condVar.wait(lock);
    while(true)
    {
        if(sendSocket->state() != QAbstractSocket::ConnectedState)
        {
            establishConnection();
        }
        short sendCount = 0;
        bool wroteSuccessfully = false;
        qint64 start = QDateTime::currentMSecsSinceEpoch();
        qint64 end = start + 1000;
        while(sendCount++ < glv::eps)
        {
            glv::mutReady.try_lock();
            if(!glv::logQueue.empty())
            {
                QByteArray log = glv::logQueue.front();
                glv::logQueue.pop();
                glv::mutReady.unlock();
                start = QDateTime::currentMSecsSinceEpoch();
                sendSocket->write(log);
                sendSocket->close();
                wroteSuccessfully = true;
            }
            else
            {
                glv::mutReady.unlock();
            }
        }
        if(wroteSuccessfully)
            cout << "Sent " << sendCount - 1 << " packets in " <<
                    (start < end ? end - start : start - end + 1000) <<
                    " milli seconds\n";
    }
}
