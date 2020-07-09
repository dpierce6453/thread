//
// Created by harldanp on 7/7/2020.
//

#include <iostream>
#include "thread1.h"

using namespace std;

void thread1::operator()() {
    cout << getBanner() << endl;

}

const string &thread1::getBanner() const {
    return banner;
}

thread1::thread1(const string &banner) : banner(banner) {}
