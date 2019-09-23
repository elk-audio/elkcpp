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

TEST_F(SushiClientTest, SetTempoPositive)
{
    sushi_controller::ControlStatus status = controller.set_tempo(200.0f);
    ASSERT_EQ(status, sushi_controller::ControlStatus::OK);
    ASSERT_EQ(controller.get_tempo(),200.0f);
}

TEST_F(SushiClientTest, GetTimeSignature)
{
    sushi_controller::TimeSignature result = controller.get_time_signature();
    ASSERT_EQ(result.numerator,sushi_controller::expected_results::TIME_SIGNATURE.numerator);
    ASSERT_EQ(result.denominator,sushi_controller::expected_results::TIME_SIGNATURE.denominator);
}

TEST_F(SushiClientTest, SetTimeSignature)
{
    sushi_controller::TimeSignature modified_time_signature{6,8};
    sushi_controller::ControlStatus status = controller.set_time_signature(modified_time_signature);
    ASSERT_EQ(status, sushi_controller::ControlStatus::OK);
    sushi_controller::TimeSignature result = controller.get_time_signature();
    ASSERT_EQ(result.numerator, modified_time_signature.numerator);
    ASSERT_EQ(result.denominator, modified_time_signature.denominator);
}

TEST_F(SushiClientTest, GetTracks)
{
    std::vector<sushi_controller::TrackInfo> track_info_list = controller.get_tracks();
    for(uint i = 0; i < track_info_list.size(); ++i)
    {
        ASSERT_EQ(track_info_list.at(i).id,sushi_controller::expected_results::TRACK_INFO_LIST.at(i).id);
        ASSERT_EQ(track_info_list.at(i).label,sushi_controller::expected_results::TRACK_INFO_LIST.at(i).label);
        ASSERT_EQ(track_info_list.at(i).name,sushi_controller::expected_results::TRACK_INFO_LIST.at(i).name);
        ASSERT_EQ(track_info_list.at(i).input_channels,sushi_controller::expected_results::TRACK_INFO_LIST.at(i).input_channels);
        ASSERT_EQ(track_info_list.at(i).input_busses,sushi_controller::expected_results::TRACK_INFO_LIST.at(i).input_busses);
        ASSERT_EQ(track_info_list.at(i).output_channels,sushi_controller::expected_results::TRACK_INFO_LIST.at(i).output_channels);
        ASSERT_EQ(track_info_list.at(i).output_busses,sushi_controller::expected_results::TRACK_INFO_LIST.at(i).output_busses);
        ASSERT_EQ(track_info_list.at(i).processor_count,sushi_controller::expected_results::TRACK_INFO_LIST.at(i).processor_count);
    }
}