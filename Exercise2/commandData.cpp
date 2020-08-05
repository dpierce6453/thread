//
// Created by Dan on 8/3/2020.
//

#include "commandData.h"

commandData::commandData() {
    cmdStr.clear();
    cmd = 0;
}

bool commandData::isGood() const {
    if (cmdStr.empty())
        return false;
    if (cmd == 0)
        return false;
    return true;
}
