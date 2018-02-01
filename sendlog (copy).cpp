#include "sendlog.h"

SendLog::SendLog()
{
    cout << "SendLog constructor. Thread id = " << this_thread::get_id() << "\n";
}

void SendLog::establishConnection()
{
    sendSocket.connectToHost(QString::fromStdString(destination::ipAddress), destination::port);
}

void SendLog::toLocalQueue()
{
    while (true)
    {
        glv::mutLogQueue.lock();
        if(!glv::logQueue.empty())
        {
            localQueue.push(glv::logQueue.front());
            glv::logQueue.pop();
            glv::mutLogQueue.unlock();
        }
        else
            glv::mutLogQueue.unlock();
    }
}

void SendLog::sendFunction()
{
    while(true)
    {
        unique_lock<mutex> lock(glv::mutReadyBool);
        glv::condVar.wait(lock, bind(&SendLog::readyToSend, this));
        if(!(sendSocket.state() == QAbstractSocket::ConnectedState))
            establishConnection();
        QByteArray log = localQueue.front();
        localQueue.pop();
        sendSocket.write(log);
        sendSocket.close();
    }
}

bool SendLog::readyToSend()
{
    bool r;
    glv::mutReadyBool.lock();
    r = glv::ready;
    glv::mutReadyBool.unlock();
    return r;
}

void SendLog::getInputFromUser()
{
    destination::desMut.lock();
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
    destination::desMut.unlock();
}


void SendLog::send()
{
    getInputFromUser();
    establishConnection();
//    writeToLocal = new thread(toLocalQueue);
//    sendThread = new thread(sendFunction);
//    writeToLocal->join();
//    sendThread->join();
}
