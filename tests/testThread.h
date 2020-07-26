//
// Created by Dan on 7/26/2020.
//

#ifndef THREAD_TESTTHREAD_H
#define THREAD_TESTTHREAD_H


#include <SafeQueue.h>

class testThread {
public:
    testThread(SafeQueue<int> *sq, bool);

    void operator()();

private:
    SafeQueue <int> *sq;
    bool tx;

    void receive() const;
    void transmit() const;
};


#endif //THREAD_TESTTHREAD_H
