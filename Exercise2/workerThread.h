//
// Created by Dan on 8/5/2020.
//

#ifndef THREAD_WORKERTHREAD_H
#define THREAD_WORKERTHREAD_H


#include "queueThread.h"

class workerThread {
    queueThread *pQT = nullptr;


public:
    void operator()();
    workerThread(queueThread *pQt);
};


#endif //THREAD_WORKERTHREAD_H
