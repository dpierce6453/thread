//
// Created by harldanp on 7/7/2020.
//
#include <iostream>
#include <thread>
#include <gtest/gtest.h>
#include <LinesList.h>
#include "thread1.h"

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
        thread1 threadA("Hello from thread A");
        thread1 threadB("Hello from thread B");
        std::thread threadX(threadA);
        std::thread threadY(threadB);
        threadX.join();
        threadY.join();

        LinesList *ll = new LinesList(::testing::internal::GetCapturedStdout());
        ASSERT_TRUE(threadA.getBanner() == ll->getStringlist().front());
        ll->getStringlist().pop_front();
        ASSERT_TRUE(threadB.getBanner() == ll->getStringlist().front());
        delete ll;

    }

}