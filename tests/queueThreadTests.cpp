//
// Created by Dan on 8/3/2020.
//

#include <gtest/gtest.h>
#include <Exercise2/commandData.h>
#include <LinesList.h>
#include "Exercise2/queueThread.h"


namespace {

    class queueThreadTests : public ::testing::Test {
    protected:

        virtual void SetUp() {
        }

        virtual void TearDown() {
        }

        queueThreadTests() {}

        virtual ~queueThreadTests() {}
    };

    TEST_F(queueThreadTests, CreateTest)
    {
        queueThread *qt = new queueThread();
        delete qt;
    }
    TEST_F(queueThreadTests, StopCmdSet)
    {
        queueThread qt;
        ASSERT_FALSE(qt.isStopCmdSet());
        qt.setStopCmd(10);
        ASSERT_TRUE(qt.isStopCmdSet());
    }
    TEST_F(queueThreadTests, StartThreadError)
    {
        queueThread qt;
        EXPECT_THROW({
            try
            {
                qt.startThread();
            }
            catch(const QueueThreadCannotStart& e)
            {
                EXPECT_STREQ(qt.getQtExceptionMsg().c_str(), e.what());
                throw;
            }
        }, QueueThreadCannotStart);
    }
    TEST_F(queueThreadTests, StartThreadSuccess)
    {
        queueThread qt;
        SafeQueue<int> sq;

        commandData cd;
        cd.cmdStr = "Full Speed Ahead";
        cd.cmd = 1;

        commandData cd2;
        cd2.cmdStr = "All Engines Stop";
        cd2.cmd = 2;

        std::string threadName = "Test Thread #1";
        qt.setStopCmd(100);
        qt.setpSQ(&sq);
        qt.setCmdData(cd);
        qt.setCmdData(cd2);
        qt.setThreadName(threadName);
        qt.setEcho(true);
        qt.setDelay(50);

        ::testing::internal::CaptureStdout();
        qt.startThread();
        sq.push(1);
        sq.push(2);
        sq.push(3);
        sq.push(100);
        qt.waitForThreadToFinish();
        LinesList *ll = new LinesList(::testing::internal::GetCapturedStdout());

        ASSERT_TRUE(ll->IsEqual(threadName + " is Running"));
        ASSERT_TRUE(ll->IsEqual(threadName + " received command: " + cd.cmdStr));
        ASSERT_TRUE(ll->IsEqual(threadName + " received command: " + cd2.cmdStr));
        ASSERT_TRUE(ll->IsEqual(threadName + " received INVALID command: " + to_string(3)));
        ASSERT_TRUE(ll->IsEqual(threadName + " stopping"));

    }

    TEST_F(queueThreadTests, commandDataTests)
    {
        commandData cd;
        ASSERT_FALSE(cd.isGood());
        cd.cmdStr = "This is the cmd string";
        ASSERT_FALSE(cd.isGood());
        cd.cmd = 1;
        ASSERT_TRUE(cd.isGood());
    }
    TEST_F(queueThreadTests, setCommandDataTests)
    {
        queueThread qt;
        commandData cd;
        ASSERT_FALSE(qt.setCmdData(cd));
        cd.cmd = 1;
        cd.cmdStr = "Full Speed Ahead";
        ASSERT_TRUE(qt.setCmdData(cd));

    }
}