//
// Created by harldanp on 7/7/2020.
//

#include <sstream>
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
