//
// Created by harldanp on 7/7/2020.
//

#include <gtest/gtest.h>
#include "LinesList.h"

namespace {

    class LineListTests : public ::testing::Test
    {
    protected:

    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }

    LineListTests() {}
    virtual ~LineListTests() {}

    };



    TEST_F(LineListTests, FirstTest)
    {
        LinesList *ll = new LinesList("This is a test string\n");
        ASSERT_TRUE(ll != nullptr);
        delete ll;
    }

    TEST_F(LineListTests, TestOneLine)
    {
        std::string str = "This is the first line\n";
        LinesList *ll = new LinesList(str);
        ASSERT_TRUE(ll->getNumberOfLines() == 1);
        list<std::string> sl = ll->getStringlist();
        str.pop_back(); //delete \n
        ASSERT_STREQ(sl.front().c_str(), str.c_str());
        delete ll;
    }

    TEST_F(LineListTests, TestMultipleLines)
    {
        list<string> teststrings;

        std::string str1 = "This is the first line\n";
        std::string str2 = "This is the second line\n";
        std::string str3 = "This is the third line";  // you can have an endl here or not.  does not matter.
        teststrings.push_back(str1);
        teststrings.push_back(str2);
        teststrings.push_back(str3);

        LinesList *ll = new LinesList(str1+ str2 + str3);
        ASSERT_TRUE(ll->getNumberOfLines() == 3);

        for(string & str: teststrings)
        {
            if (str.back() == '\n') str.pop_back();
            ASSERT_STREQ(ll->getStringlist().front().c_str(), str.c_str());
            ll->getStringlist().pop_front();
        }
        delete ll;

    }

    TEST_F(LineListTests, NoLinesTest)
    {
        LinesList *ll = new LinesList("This is a line without endl character");
        ASSERT_TRUE(ll->getNumberOfLines() == 1);
        delete ll;
    }

    TEST_F(LineListTests, IsEqualTest)
    {
        list<string> teststrings;

        std::string str1 = "This is the first line\n";
        std::string str2 = "This is the second line\n";
        std::string str3 = "This is the third line";  // you can have an endl here or not.  does not matter.

        teststrings.push_back(str1);
        teststrings.push_back(str2);
        teststrings.push_back(str3);

        LinesList *ll = new LinesList(str1+ str2 + str3);
        ASSERT_TRUE(ll->getNumberOfLines() == 3);

        for(string & str: teststrings)
        {
            if (str.back() == '\n') str.pop_back();
            ASSERT_TRUE(ll->IsEqual(str));
        }
    }

    TEST_F(LineListTests, ContainsTest)
    {
        list<string> teststrings;

        std::string str1 = "Transmit: 1\n";
        std::string str2 = "Trasnmit: 2\n";
        std::string str3 = "Receive: 1";  // you can have an endl here or not.  does not matter.

        teststrings.push_back(str1);
        teststrings.push_back(str2);
        teststrings.push_back(str3);

        LinesList *ll = new LinesList(str1+ str2 + str3);

        for(string & str: teststrings)
        {
            if (str.back() == '\n') str.pop_back();
            ASSERT_TRUE(ll->contains(str));
        }

        ASSERT_FALSE(ll->contains("Bad String"));
        delete ll;
    }
}

