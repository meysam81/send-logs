#include "GlobalVariable.h"
#include <thread>
//=================================================================================
mutex glv::mutReady;
condition_variable glv::condVar;
queue<QByteArray> glv::logQueue;
mutex glv::mutGetInput;
short glv::eps;
//=================================================================================
string destination::ipAddress;
quint16 destination::port;
mutex destination::desMut;
int main()
{
    SendLog sInput;
    thread sInputThread(&SendLog::getInputFromUser, &sInput);
    sInputThread.join();
    //=============================================================================
    cout << "Enter number of <sending threads>: ";
    short numThreads;
    cin >> numThreads;
    SendLog *s = new SendLog[numThreads];
    vector<thread> sThreads;
    for(int i = 0; i < numThreads; i++)
    {
        sThreads.push_back(thread(&SendLog::send, &s[i]));
    }
    //=============================================================================
    ReadLog r;
    thread rThread(&ReadLog::read, &r);
    //=============================================================================
    for(int i = 0; i < numThreads; i++)
        sThreads.at(i).join();
    rThread.join();
    return 0;
}
