//
// Created by Dan on 7/26/2020.
//

#include <iostream>
#include <thread>
#include <chrono>


#include "testThread.h"

void testThread::operator()() {
    int y;
    for (int i = 0; i < numloops; i++)
    {
        if(tx)
        {
            y=i;
            sq->push(y);
        } else
        {
            y=sq->pop();
        }
        randomsleep(y);
    }
}


void testThread::randomsleep(int x) const
{
    std::cout << str << x << std::endl;
    int randms = (rand() % 50) + 50;
    std::this_thread::sleep_for(std::chrono::milliseconds (randms));
}

testThread::testThread(SafeQueue<int> *sq, bool transmit):
    sq(sq),
    tx(transmit)
{
    if(tx)
    {
        str = "Transmit: ";
    } else
    {
        str = "Receive: ";
    }
    numloops = 10;
}

testThread::testThread(SafeQueue<int> *sq, bool transmit, std::string str, int numberofloops):
    sq(sq),
    tx(transmit),
    str(str),
    numloops(numberofloops)
{
}
