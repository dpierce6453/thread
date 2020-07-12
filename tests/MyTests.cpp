//
// Created by harldanp on 7/7/2020.
//
#include <iostream>
#include <thread>
#include <gtest/gtest.h>
#include <LinesList.h>
#include "thread1.h"
#include "cmd_clean.h"
#include "cmd_engine.h"

namespace {

    class MyTests : public ::testing::Test
    {
    protected:

    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }

    MyTests() {}
    virtual ~MyTests() {}

    };



    TEST_F(MyTests, FirstTest)
    {
        EXPECT_EQ(true, true);
    }



    TEST_F(MyTests, SecondTest)
    {
        ::testing::internal::CaptureStdout();
        thread1 threadA("Hello from thread A",0);
        thread1 threadB("Hello from thread B",0);
        std::thread threadX(threadA);
        std::thread threadY(threadB);
        threadX.join();
        threadY.join();

        LinesList *ll = new LinesList(::testing::internal::GetCapturedStdout());
        ASSERT_TRUE(ll->IsEqual(threadA.getBanner()));
        ASSERT_TRUE(ll->IsEqual(threadB.getBanner()));
        delete ll;
    }

    TEST_F(MyTests, TestCleaningThread)
    {
        ::testing::internal::CaptureStdout();
        cmd_clean *cmdClean = new cmd_clean();
        int numcleanings = 3;

        while(cmdClean->getTotalCleanings() < numcleanings)
        {
            cmdClean->go();
        }

        LinesList *ll = new LinesList(::testing::internal::GetCapturedStdout());
        for(int i=0; i < numcleanings; i++)
        {
            ASSERT_TRUE(ll->IsEqual(cmdClean->str2));
            ASSERT_TRUE(ll->IsEqual(cmdClean->str1));
        }
        delete ll;
        delete cmdClean;

    }

    TEST_F(MyTests, TestEngineFullSpeedAhead)
    {
        ::testing::internal::CaptureStdout();
        string str = "Full Speed Ahead";
        cmd_engine *cmdFullSpeedAhead = new cmd_engine(str);
        cmdFullSpeedAhead->go();

        LinesList *ll = new LinesList(::testing::internal::GetCapturedStdout());
        ASSERT_TRUE(ll->IsEqual(cmdFullSpeedAhead->str2));
        ASSERT_TRUE(ll->IsEqual(str));

        delete ll;
        delete cmdFullSpeedAhead;
    }

}