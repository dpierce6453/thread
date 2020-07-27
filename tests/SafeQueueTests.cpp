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

    public:
        void createTestStrings(const string &str, const int numloops, list<std::string> &checkstrings) const
        {
            for(int i=0; i<numloops; i++)
            {
                std::string st = str + std::to_string(i);
                checkstrings.push_back(st);
            }
        }

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
        const std::string strtx = "Transmit: ";
        const std::string strrx = "Receive: ";
        const int numloops = 10;

        list<std::string> checkstrings;
        createTestStrings(strtx, numloops, checkstrings);
        createTestStrings(strrx, numloops, checkstrings);

        ::testing::internal::CaptureStdout();
        SafeQueue <int> sq;
        testThread tx(&sq, true, strtx, numloops);
        testThread rx(&sq, false, strrx, numloops);
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

