//
// Created by Dan on 8/3/2020.
//

#include <iostream>
#include <interface.pb.h>

#include "queueThread.h"
#include "workerThread.h"

void queueThread::threadWorker()
{
    if(echo)
    {
        std::cout << threadName << " is Running" << std::endl;
    }
    std::string cmd;
    while(true)
    {
        cmd = pSQ->pop();
        gpc::Command rxCommand;
        if (rxCommand.ParseFromString(cmd) == false) break;  // should throw an exception here
        if(rxCommand.cmd() == stopCmd) break;

        std::vector<commandData>::iterator it;
        for(it=cdVec.begin() ; it != cdVec.end(); it++)
        {
            if(rxCommand.cmd() == it->cmd)
            {
                std::cout << threadName << " received command: " << it->cmdStr << std::endl;
                break;
            }
        }
        if(it == cdVec.end())
        {
           std::cout << threadName << " received INVALID command: " << rxCommand.cmd() << std::endl;
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
    for(const commandData &cd : cdVec)
    {
        if(cd.isGood() == false) return false;
    }
    return true;
}

bool queueThread::setCmdData(commandData &cd) {
    bool ret = false;
    if( cd.isGood() )
    {
        cdVec.push_back(cd);
        ret=true;
    }
    return ret;
}

bool queueThread::isQueueSet() const {
    if(pSQ == nullptr)
    {
        return false;
    }
    return true;
}


bool queueThread::isReady() const { return isStopCmdSet() && isCmdDataGood() && isQueueSet(); }

void queueThread::setDelay(int delay) {
    queueThread::delay = delay;
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

bool queueThread::isStopCmdSet() const {
    return (stopCmd != 0);
}

void queueThread::setStopCmd(int stopCmd) {
    queueThread::stopCmd = stopCmd;
}

const std::string &queueThread::getQtExceptionMsg() const {
    return qtExceptionMsg;
}

queueThread::queueThread() {
    threadName = "Thread has no name";
}

queueThread::~queueThread() {
}
