//
// Created by Dan on 7/26/2020.
//

#include <iostream>
#include <thread>
#include <chrono>


#include "testThread.h"

void testThread::operator()() {
    if(tx)
    {
        transmit();
    } else
    {
        receive();
    }
}

void testThread::receive() const {
    int i=0;
    while(i<10)
    {
        int rx = sq->pop();
        std::cout << "Received: " << rx << std::endl;
        i++;
        std::this_thread::sleep_for(std::chrono::milliseconds (100));
    }
}

testThread::testThread(SafeQueue<int> *sq, bool transmit): sq(sq) {
    this->tx = transmit;
}

void testThread::transmit() const {
    int i=0;
    while (i<10)
    {
        sq->push(i);
        std::cout << "Transmit: " << i << std::endl;
        i++;
        std::this_thread::sleep_for(std::chrono::milliseconds (50));
    }
}
