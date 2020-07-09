//
// Created by harldanp on 7/7/2020.
//

#ifndef THREAD_THREAD1_H
#define THREAD_THREAD1_H

#include <string>


class thread1 {
public:
    thread1(const std::string &banner);

    void operator()();
    const std::string &getBanner() const;

private:
    const std::string banner = {"Hello from the thread1 class"};

};


#endif //THREAD_THREAD1_H
