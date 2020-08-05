//
// Created by Dan on 8/5/2020.
//

#include <iostream>
#include "workerThread.h"

workerThread::workerThread(queueThread *pQt) : pQT(pQt) {}

void workerThread::operator()() {
    pQT->threadWorker();
}