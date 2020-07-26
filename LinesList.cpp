//
// Created by harldanp on 7/7/2020.
//

#include <sstream>
#include <algorithm>
#include "LinesList.h"


LinesList::LinesList(const string &string1) : string1(string1) { findlines(); }

int LinesList::getNumberOfLines() const {
    return numberOfLines;
}

void LinesList::findlines() {
    //This function will separate the inputed string into lines.
    std:istringstream ss(string1);
    string str;
    while(std::getline(ss, str))
    {
        if(str.back() == '\n') str.pop_back();
        stringlist.push_back(str);
        numberOfLines++;
    }

}

list<string> & LinesList::getStringlist()  {
    return stringlist;
}

bool LinesList::IsEqual(const string &str) {
    if(numberOfLines > 0)
    {
        if(stringlist.front() == str)
        {
            stringlist.pop_front();
            return true;
        }
    }
    return false;
}

bool LinesList::contains(const string &str) {
    string str1 = stringlist.front();
    bool ret = false;
    auto it = std::find(stringlist.begin(), stringlist.end(), str1);
    if (it != stringlist.end())
        ret = true;
    return (stringlist.end() != it);
}
