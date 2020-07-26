//
// Created by Dan on 7/26/2020.
//

#include <gtest/gtest.h>
#include <thread>
#include <LinesList.h>
#include "SafeQueue.h"
#include "testThread.h"

void TestThreadRec(SafeQueue<int> &sq);
void TestThreadTx(SafeQueue<int> &sq);
namespace {

    class SafeQueueTests : public ::testing::Test {
    protected:

        virtual void SetUp() {
        }

        virtual void TearDown() {
        }

        SafeQueueTests() {}

        virtual ~SafeQueueTests() {}

    };


    TEST_F(SafeQueueTests, FirstTest) {
        SafeQueue <int> *sq= new SafeQueue<int>();
        ASSERT_TRUE(sq != nullptr);
        delete sq;
    }

    TEST_F(SafeQueueTests, PushPopTest)
    {
        SafeQueue <int> *sq = new SafeQueue<int>();
        sq->push(1);
        ASSERT_FALSE(sq->isEmpty());
        ASSERT_TRUE(sq->pop() == 1);
        delete sq;
    }

    TEST_F(SafeQueueTests, ThreadTest)
    {
        list<std::string> checkstrings;
        for(int i=0; i<10; i++)
        {
            std::string st = "Transmit: " + i;
            checkstrings.push_back(st);
        }
        for(int i=0; i<10; i++)
        {
            std::string st = "Receive: " + i;
            checkstrings.push_back(st);
        }

        ::testing::internal::CaptureStdout();
        SafeQueue <int> sq;
        testThread tx(&sq, true);
        testThread rx(&sq, false);
        std::thread threadX(tx);
        std::thread threadY(rx);
        threadY.join();
        threadX.join();

        LinesList *ll = new LinesList(::testing::internal::GetCapturedStdout());
        while(!checkstrings.empty())
        {
            std::string str = checkstrings.front();
            ASSERT_TRUE(ll->contains(str));
            checkstrings.pop_front();
        }
        delete ll;

    }

}

