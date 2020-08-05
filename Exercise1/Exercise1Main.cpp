//
// Created by Dan on 8/3/2020.
//

#include <map>

#include "thread1.h"
#include "command.h"
#include "cmd_clean.h"
#include "cmd_engine.h"

float getDouble( void );
void buildMap(std::map<int, command*> &commandMap);
void deleteMap(std::map<int, command*> &commandMap);

int Ex1Main() {
    float com = 0;
    std::map<int, command*> commandMap;
    buildMap(commandMap);

    while(com != 100)
    {
        com = getDouble();
        std::map<int, command*>::iterator it;
        it = commandMap.find(com);
        if(it != commandMap.end())
        {
            it->second->go();
        }
    }

    deleteMap(commandMap);
    return 0;
}

void buildMap(std::map<int, command*> &commandMap)
{
    // factory for the command objects.
    commandMap[1] = new cmd_clean();
    commandMap[2] = new cmd_engine("Full Speed Ahead");
    commandMap[3] = new cmd_engine("Full Stop");
}
void deleteMap(std::map<int, command*> &commandMap)
{
    for(auto const& x: commandMap)
    {
        delete(x.second);
    }
}