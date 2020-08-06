//
// Created by Dan on 8/3/2020.
//

#ifndef THREAD_QUEUETHREAD_H
#define THREAD_QUEUETHREAD_H


#include <vector>
#include <thread>
#include "QueueThreadCannotStart.h"
#include "commandData.h"
#include "../SafeQueue.h"

class queueThread {

    int stopCmd = 0;

private:
    const std::string qtExceptionMsg = "QueueThread cannot start:  Critical Data Missing";
    std::string threadName;
    std::vector<commandData> cdVec;
    bool isCmdDataGood() const;
    SafeQueue<std::string> *pSQ = nullptr;
    int delay = 1000;
    bool echo = false;
    std::thread *pThisThread = nullptr;
    bool isQueueSet() const;
    bool isReady() const;

public:
    void setDelay(int delay);
    void setEcho(bool echo);
    void setThreadName(const std::string &threadName);
    void setpSQ(SafeQueue<std::string> *pSq);
    bool setCmdData(commandData &cd);
    void setStopCmd(int stopCmd);
    const std::string &getQtExceptionMsg() const;

    bool isStopCmdSet() const;

    void startThread() ;
    void threadWorker();
    void waitForThreadToFinish();

    queueThread();
    virtual ~queueThread();

};


#endif //THREAD_QUEUETHREAD_H
