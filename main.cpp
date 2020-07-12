#include <iostream>
#include <thread>
#include <cmath>
#include <map>
#include "thread1.h"
#include "command.h"
#include "cmd_clean.h"
#include "cmd_engine.h"

float getDouble( void );
void buildmap(std::map<int, command*> &commandMap);
void deleteMap(std::map<int, command*> &commandMap);

int main() {

    float com = 0;
    std::map<int, command*> commandMap;
    buildmap(commandMap);

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

void buildmap(std::map<int, command*> &commandMap)
{
    // factory for the command objects.
    commandMap[1] = new cmd_clean();
    commandMap[2] = new cmd_engine("Full Speed Ahead");
    commandMap[3] = new cmd_engine("Full Stop");
}
void deleteMap(std::map<int, command*> &commandMap)
{
    delete commandMap[1];
    delete commandMap[2];
    delete commandMap[3];
}

float getDouble( void ) {
    float command = 0;
    std::cout << "Enter Command" << std::endl;
    std::cin >> command;
    command = std::floor(command);
    if(std::cin.fail() || std::isnan(command))
    {
        std::cout << "Invalid Input"  << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        command = 0;

    } else
    {
        std::cout << "Command is: " << command << std::endl;
    }
    return command;
}
