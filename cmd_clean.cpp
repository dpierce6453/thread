//
// Created by Dan on 7/12/2020.
//

#include <iostream>

#include "cmd_clean.h"

cmd_clean::cmd_clean() :
cleaning_thread(nullptr), total_cleanings(0)
{
    pMythread = new thread1(str1,100);
}

cmd_clean::~cmd_clean() {
    waitforthreadtofinish();
    delete pMythread;
}

void cmd_clean::go(void)
{
    waitforthreadtofinish();
    cleaning_thread = new std::thread(*pMythread);
    total_cleanings++;
}

void cmd_clean::waitforthreadtofinish() {
    if (cleaning_thread != nullptr)
    {
        std::cout << str2 << std::endl;
        cleaning_thread->join();
        delete cleaning_thread;
        cleaning_thread = nullptr;
    }
}

int cmd_clean::getTotalCleanings() const {
    return total_cleanings;
}
