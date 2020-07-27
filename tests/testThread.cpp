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
    while(i<numloops)
    {
        int rx = sq->pop();
        std::cout << str << rx << std::endl;
        i++;
        std::this_thread::sleep_for(std::chrono::milliseconds (100));
    }
}

testThread::testThread(SafeQueue<int> *sq, bool transmit): sq(sq), tx(transmit) {
    if(tx)
    {
        str = "Transmit: ";
    } else
    {
        str = "Receive: ";
    }
    numloops = 10;
}

void testThread::transmit() const {
    int i=0;
    while (i<numloops)
    {
        sq->push(i);
        std::cout << str << i << std::endl;
        i++;
        std::this_thread::sleep_for(std::chrono::milliseconds (50));
    }
}

testThread::testThread(SafeQueue<int> *sq, bool transmit, std::string str, int numberofloops):
    sq(sq),
    tx(transmit),
    str(str),
    numloops(numberofloops)
{
}
