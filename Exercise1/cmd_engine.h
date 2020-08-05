//
// Created by Dan on 7/12/2020.
//

#ifndef THREAD_CMD_ENGINE_H
#define THREAD_CMD_ENGINE_H

#include <string>
#include <thread>

#include "command.h"
#include "thread1.h"

class cmd_engine : public command {
private:
    const std::string str;
    thread1 *pMythread;
    std::thread *engine_thread = nullptr;
    int total_commands = 0;
public:
    const std::string str2 = "Executing Engine Command";
    int getTotalCommands() const;

public:
    void go ( void ) final;
    cmd_engine(const std::string &str);
    virtual ~cmd_engine();
};


#endif //THREAD_CMD_ENGINE_H
