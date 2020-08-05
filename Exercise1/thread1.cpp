//
// Created by harldanp on 7/7/2020.
//

#include <iostream>
#include <chrono>
#include <thread>
#include "thread1.h"

using namespace std;

void thread1::operator()() {
    cout << getBanner() << endl;
    this_thread::sleep_for(chrono::milliseconds (delay));

}

const string &thread1::getBanner() const {
    return banner;
}

thread1::thread1(const string &banner) : banner(banner), delay(0) {}

thread1::thread1(const string &banner, int delay) : banner(banner), delay(delay) {}
