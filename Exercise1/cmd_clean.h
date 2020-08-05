//
// Created by Dan on 7/12/2020.
//

#ifndef THREAD_CMD_CLEAN_H
#define THREAD_CMD_CLEAN_H

#include <string>
#include <thread>
#include "command.h"
#include "thread1.h"


class cmd_clean : public command {
public:
    const std::string str1 = "Hello from the Cleaning Thread.  Cleaning now...";
    const std::string str2 = "Waiting on last cleaning job to finish";
    void go(void ) final;
    cmd_clean();
    virtual ~cmd_clean();

private:
    thread1 *pMythread;
    std::thread *cleaning_thread = nullptr;
    int total_cleanings;
public:
    void waitforthreadtofinish();
    int getTotalCleanings() const;

};


#endif //THREAD_CMD_CLEAN_H
