//
// Created by Dan on 7/26/2020.
//

#ifndef THREAD_TESTTHREAD_H
#define THREAD_TESTTHREAD_H


#include <SafeQueue.h>

class testThread {
public:
    testThread(SafeQueue<int> *sq, bool);
    testThread(SafeQueue<int> *sq, bool, std::string str, int numberofloops);

    void operator()();

private:
    SafeQueue <int> *sq;
    bool tx;
    std::string str;
    int numloops;

    void receive() const;
    void transmit() const;
};


#endif //THREAD_TESTTHREAD_H
