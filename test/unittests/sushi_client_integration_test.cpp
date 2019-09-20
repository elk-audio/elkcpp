#include <thread>
#include <unistd.h>

#include "gtest/gtest.h"


#include "sushi_grpc_client.h"
#include "test_utils/sushi_server_mockup.h"
#define private public


// A more complex test case where tests can be grouped
// And setup and teardown functions added.
class SushiClientTest : public ::testing::Test
{
    protected:
    SushiClientTest()
    {
    }
    void SetUp()
    {
        //sushi_controller::RunServerMockup();
        server_thread = std::thread(sushi_controller::RunServerMockup);
        usleep(500);
        controller.reset(new sushi_controller::SushiControllerClient("localhost:51051"));
    }

    void TearDown()
    {
        sushi_controller::KillServerMockup();
        server_thread.join();
    }

    std::unique_ptr<sushi_controller::SushiControllerClient> controller{};
    std::thread server_thread;
};

TEST_F(SushiClientTest, GetSampleRate)
{
    ASSERT_FLOAT_EQ(controller.get()->get_samplerate(),sushi_controller::expected_results::SAMPLERATE);
}
TEST_F(SushiClientTest, GetPlayingMode)
{
    ASSERT_EQ(controller.get()->get_playing_mode(), sushi_controller::expected_results::PLAYING_MODE);
}