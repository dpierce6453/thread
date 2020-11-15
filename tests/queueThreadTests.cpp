//
// Created by Dan on 8/3/2020.
//

#include <gtest/gtest.h>
#include <interface.pb.h>

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
        SafeQueue<std::string> sq;

        const std::string str1 = "Full Speed Ahead";
        const std::string str2 = "All Engines Stop";

        std::string threadName = "Test Thread #1";
        qt.setpSQ(&sq);
        qt.setCmdData(gpc::FULL_STEAM_AHEAD);
        qt.setCmdData(gpc::ALL_ENGINES_STOP);
        qt.setThreadName(threadName);
        qt.setEcho(true);
        qt.setDelayGoodCmd(50);

        ::testing::internal::CaptureStdout();
        qt.startThread();
        gpc::Command command;
        command.set_cmd(gpc::FULL_STEAM_AHEAD);
        command.set_cmdstr(str1);
        sq.push(command.SerializeAsString());
        command.set_cmd(gpc::ALL_ENGINES_STOP);
        command.set_cmdstr(str2);
        sq.push(command.SerializeAsString());
        command.set_cmd(gpc::CLEAN_SHIP);
        command.set_cmdstr("Invalid Command");
        sq.push(command.SerializeAsString());
        command.set_cmd(gpc::STOP_PROCESSING_CMDS);
        command.set_cmdstr("Stop Thread");
        sq.push(command.SerializeAsString());

        qt.waitForThreadToFinish();
        LinesList *ll = new LinesList(::testing::internal::GetCapturedStdout());

        ASSERT_TRUE(ll->IsEqual(threadName + " is Running"));
        ASSERT_TRUE(ll->IsEqual(threadName + " received command: " + str1));
        ASSERT_TRUE(ll->IsEqual(threadName + " received command: " + str2));
        ASSERT_TRUE(ll->IsEqual(threadName + " received INVALID command: " + to_string(3)));
        ASSERT_TRUE(ll->IsEqual(threadName + " stopping"));

    }


    TEST_F(queueThreadTests, setCommandDataTests)
    {
        queueThread qt;
        ASSERT_TRUE(qt.setCmdData(gpc::FULL_STEAM_AHEAD));
        ASSERT_TRUE(qt.setCmdData(gpc::ALL_ENGINES_STOP));

    }
}