#include <iostream>
#include <thread>
#include <cmath>

float getDouble( void );

int Ex1Main();
int Ex2Main();

int main() {

    return Ex2Main();

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
