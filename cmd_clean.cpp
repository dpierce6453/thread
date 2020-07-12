//
// Created by Dan on 7/12/2020.
//

#include <iostream>

#include "cmd_clean.h"

cmd_clean::cmd_clean() :
cleaning_thread(nullptr)
{
    pMythread = new thread1(str1,100);
}

cmd_clean::~cmd_clean() {
    delete pMythread;
}

void cmd_clean::go(void) {

    if(cleaning_thread == nullptr)
    {
        cleaning_thread = new std::thread(*pMythread);
    }
    else
    {
        std::cout << str2 << std::endl;
        cleaning_thread->join();
        delete cleaning_thread;
        cleaning_thread = nullptr;
        total_cleanings++;
    }
}

int cmd_clean::getTotalCleanings() const {
    return total_cleanings;
}
