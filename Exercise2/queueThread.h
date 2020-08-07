//
// Created by Dan on 8/3/2020.
//

#ifndef THREAD_QUEUETHREAD_H
#define THREAD_QUEUETHREAD_H


#include <vector>
#include <thread>
#include <interface.pb.h>

#include "QueueThreadCannotStart.h"
#include "../SafeQueue.h"

class queueThread {

private:
    const std::string qtExceptionMsg = "QueueThread cannot start:  Critical Data Missing";
    std::string threadName = "Thread has no name";
    std::vector<gpc::CmdType> cdVec;
    SafeQueue<std::string> *pSQ = nullptr;
    int delay = 1000;
    bool echo = false;
    std::thread *pThisThread = nullptr;

    bool isCmdDataGood() const;
    bool isQueueSet() const;
    bool isReady() const;
    void threadWorker();

public:
    void setDelay(int delay);
    void setEcho(bool echo);
    void setThreadName(const std::string &threadName);
    void setpSQ(SafeQueue<std::string> *pSq);
    bool setCmdData(gpc::CmdType cmd);
    const std::string &getQtExceptionMsg() const;

    void startThread() ;
    void waitForThreadToFinish();

    queueThread();
    virtual ~queueThread();

    friend class workerThread;

};


#endif //THREAD_QUEUETHREAD_H
