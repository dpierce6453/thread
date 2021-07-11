//
// Created by Dan on 8/3/2020.
//

#include <iostream>

#include "queueThread.h"
#include "workerThread.h"

void queueThread::threadWorker()
{
    if(echo)
    {
        std::cout <<  threadName << " is Running" << std::endl;
    }
    while(true)
    {
        std::string cmd = pSQ->pop();
        int delay = delayGoodCmd;

        gpc::Command rxCommand;
        if (!rxCommand.ParseFromString(cmd))
            continue;  // should throw an exception here

        if(rxCommand.cmd() == gpc::STOP_PROCESSING_CMDS)
            break;

        std::vector<gpc::CmdType>::iterator it;
        it = std::find(cdVec.begin(), cdVec.end(), rxCommand.cmd());
        if(it != cdVec.end())
        {
            std::cout << threadName << " received command: " << rxCommand.cmdstr() << std::endl;
        }
        else
        {
           std::cout << threadName << " received INVALID command: " << rxCommand.cmd() << std::endl;
           delay = delayBadCmd;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds (delay));
    }
    if(echo)
    {
        std::cout << threadName << " stopping" << std::endl;
    }
}

void queueThread::startThread()  {
    if(isReady())
    {
        workerThread wt(this);
        //passing an object to std::thread with the () overridden will use that function as the thread function.
        pThisThread = new std::thread(wt);
    }
    else
    {
        throw QueueThreadCannotStart(qtExceptionMsg);
    }
}

bool queueThread::isCmdDataGood() const {
    if( cdVec.empty() )
        return false;
    return (std::all_of(cdVec.begin(),cdVec.end(), [](gpc::CmdType c){return gpc::CmdType_IsValid(c);}));
}

bool queueThread::setCmdData(gpc::CmdType cmd) {
    cdVec.push_back(cmd);
    return true;
}

bool queueThread::isQueueSet() const {
    if(pSQ == nullptr)
    {
        return false;
    }
    return true;
}


bool queueThread::isReady() const { return isCmdDataGood() && isQueueSet(); }

void queueThread::setDelayGoodCmd(int delay) {
    queueThread::delayGoodCmd = delay;
}

void queueThread::setpSQ(SafeQueue<std::string> *pSq) {
    pSQ = pSq;
}

void queueThread::setThreadName(const std::string &threadName) {
    queueThread::threadName = threadName;
}

void queueThread::setEcho(bool echo) {
    queueThread::echo = echo;
}

void queueThread::waitForThreadToFinish() {
    pThisThread->join();
}


const std::string &queueThread::getQtExceptionMsg() const {
    return qtExceptionMsg;
}

queueThread::queueThread() {
}

queueThread::~queueThread() {
}

void queueThread::setDelayBadCmd(int delayBadCmd) {
    queueThread::delayBadCmd = delayBadCmd;
}
