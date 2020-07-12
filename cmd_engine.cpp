//
// Created by Dan on 7/12/2020.
//

#include <iostream>
#include "cmd_engine.h"

void cmd_engine::go(void)
{
    std::cout << str2 << std::endl;
    engine_thread = new std::thread(*pMythread);
    engine_thread->join();
    delete engine_thread;
    total_commands++;
}

cmd_engine::cmd_engine(const std::string &str) : str(str)
{
    pMythread = new thread1(str,100);
}

cmd_engine::~cmd_engine() {
    delete pMythread;
}

int cmd_engine::getTotalCommands() const {
    return total_commands;
}
