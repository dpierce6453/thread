//
// Created by Dan on 11/15/2020.
//

#include "queueThread.h"
//#include <interface.pb.h>


float getDouble( void );

int Ex2Main()
{
    float command = 0;
    
    SafeQueue<std::string> sqEngine;
    SafeQueue<std::string> sqClean;

    queueThread qtEngine;
    queueThread qtClean;

    qtEngine.setpSQ(&sqEngine);
    qtEngine.setCmdData(gpc::FULL_STEAM_AHEAD);
    qtEngine.setCmdData(gpc::ALL_ENGINES_STOP);
    qtEngine.setThreadName("Engine Thread");
    qtEngine.setEcho(true);
    qtEngine.setDelayGoodCmd(1000);
    qtEngine.setDelayBadCmd(2000);

    qtClean.setpSQ(&sqClean);
    qtClean.setCmdData(gpc::CLEAN_SHIP);
    qtClean.setThreadName("Cleaning Thread");
    qtClean.setEcho(true);
    qtClean.setDelayGoodCmd(1000);
    qtClean.setDelayBadCmd(2000);

    qtEngine.startThread();
    qtClean.startThread();

    while(1)
    {
        command = getDouble();
        if(gpc::CmdType_IsValid(int(command)))
        {
            gpc::Command cmd;
            cmd.set_cmd(gpc::CmdType(command));
            cmd.set_cmdstr(gpc::CmdType_Name(int(command)));
            sqClean.push(cmd.SerializeAsString());
            sqEngine.push(cmd.SerializeAsString());
            if(command == gpc::STOP_PROCESSING_CMDS) break;
        }
    }
    qtClean.waitForThreadToFinish();
    qtEngine.waitForThreadToFinish();

    return 0;
    
}