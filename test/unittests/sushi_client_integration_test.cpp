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
    }

    void TearDown()
    {
    }
    sushi_controller::SushiServerMockup server;
    sushi_controller::SushiControllerClient controller{"localhost:51051"};
};

TEST_F(SushiClientTest, GetSampleRate)
{
    ASSERT_FLOAT_EQ(controller.get_samplerate(),sushi_controller::expected_results::SAMPLERATE);
}
TEST_F(SushiClientTest, GetPlayingMode)
{
    ASSERT_EQ(controller.get_playing_mode(), sushi_controller::expected_results::PLAYING_MODE);
}

TEST_F(SushiClientTest, SetPlayingMode)
{
    controller.set_playing_mode(sushi_controller::PlayingMode::STOPPED);
    ASSERT_EQ(controller.get_playing_mode(),sushi_controller::PlayingMode::STOPPED);
    controller.set_playing_mode(sushi_controller::PlayingMode::PLAYING);
    ASSERT_EQ(controller.get_playing_mode(),sushi_controller::PlayingMode::PLAYING);
    controller.set_playing_mode(sushi_controller::PlayingMode::RECORDING);
    ASSERT_EQ(controller.get_playing_mode(),sushi_controller::PlayingMode::RECORDING);
}

TEST_F(SushiClientTest, GetSyncMode)
{
    ASSERT_EQ(controller.get_sync_mode(), sushi_controller::expected_results::SYNC_MODE);
}

TEST_F(SushiClientTest, SetSyncMode)
{
    controller.set_sync_mode(sushi_controller::SyncMode::INTERNAL);
    ASSERT_EQ(controller.get_sync_mode(),sushi_controller::SyncMode::INTERNAL);
    controller.set_sync_mode(sushi_controller::SyncMode::MIDI);
    ASSERT_EQ(controller.get_sync_mode(),sushi_controller::SyncMode::MIDI);
    controller.set_sync_mode(sushi_controller::SyncMode::LINK);
    ASSERT_EQ(controller.get_sync_mode(),sushi_controller::SyncMode::LINK);
}

TEST_F(SushiClientTest, GetTempo)
{
    ASSERT_EQ(controller.get_tempo(),sushi_controller::expected_results::TEMPO);
}