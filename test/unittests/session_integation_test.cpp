#include <gtest/gtest.h>

#include "sushi_client.h"
#include "session_controller.cpp"
#include "test_utils/session_server_mockup.h"
#define private public

class SessionControllerTest : public ::testing::Test
{
protected:
    SessionControllerTest()
    {

    }
    void SetUp()
    {

    }

    void TearDown()
    {

    }
    sushi_controller::SessionServerMockup server;
    std::shared_ptr<sushi_controller::SessionController> controller = sushi_controller::CreateSessionController("localhost:51051");
};

TEST_F(SessionControllerTest, SaveBinaryState)
{
    auto result = controller->save_binary_session();
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result.first);
    ASSERT_EQ(std::string(expected_results::STATE.begin(), expected_results::STATE.end()), result.second);
}

TEST_F(SessionControllerTest, RestoreBinaryState)
{
    auto result = controller->restore_binary_session(std::string(expected_results::STATE.begin(), expected_results::STATE.end()));
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result);
}
