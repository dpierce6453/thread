#include <iostream>
#include <thread>
#include "thread1.h"

int main() {

    thread1 t1("Hello from thread 1");
    std::thread thread1(t1);
    thread1.join();
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
