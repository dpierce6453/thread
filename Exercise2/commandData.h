//
// Created by Dan on 8/3/2020.
//

#ifndef THREAD_COMMANDDATA_H
#define THREAD_COMMANDDATA_H

#include <string>

class commandData {
public:
    std::string cmdStr;
    int cmd;
    bool isGood() const;

    commandData();
};


#endif //THREAD_COMMANDDATA_H
