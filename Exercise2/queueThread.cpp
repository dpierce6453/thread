//
// Created by Dan on 8/3/2020.
//

#include <iostream>
#include "queueThread.h"
#include "workerThread.h"


void queueThread::startThread()  {
    if(isStopCmdSet() && isCmdDataGood() && isQueueSet())
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
    if( cdVec.empty())
        return false;
    for(const commandData &cd : cdVec)
    {
        if(cd.isGood() == false) return false;
    }
    return true;
}

bool queueThread::setCmdData(commandData &cd) {
    if(cd.isGood() == false)
    {
        return false;
    } else
    {
        cdVec.push_back(cd);
    }
    return true;
}

bool queueThread::isQueueSet() const {
    if(pSQ == nullptr)
    {
        return false;
    }
    return true;
}

void queueThread::threadWorker()
{
    if(echo)
    {
        std::cout << threadName << " is Running" << std::endl;
    }
    int cmd;
    while((cmd = pSQ->pop()) != stopCmd)
    {
        std::vector<commandData>::iterator it = cdVec.begin();
        for(it; it != cdVec.end(); it++)
        {
            if(cmd == it->cmd)
            {
                std::cout << threadName << " received command: " << it->cmdStr << std::endl;
                break;
            }
        }
        if(it == cdVec.end())
        {
           std::cout << threadName << " received INVALID command: " << cmd << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds (delay));
    }
    if(echo)
    {
        std::cout << threadName << " stopping" << std::endl;
    }
}

void queueThread::setDelay(int delay) {
    queueThread::delay = delay;
}

void queueThread::setpSQ(SafeQueue<int> *pSq) {
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
