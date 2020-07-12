//
// Created by harldanp on 7/7/2020.
//

#ifndef THREAD_LINESLIST_H
#define THREAD_LINESLIST_H

#include <string>
#include <list>

using namespace std;

class LinesList {
public:

    LinesList(const string &string1);

private:
    list<string> stringlist;
    void findlines();
    string string1;
    int numberOfLines = 0;
public:
    list <string> & getStringlist();
    int getNumberOfLines() const;
    bool IsEqual(const string &str);

};


#endif //THREAD_LINESLIST_H
