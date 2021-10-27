#include <gtest/gtest.h>

#include "sushi_client.h"
#include "transport_controller.cpp"
#include "test_utils/transport_server_mockup.h"
#define private public


class TransportControllerTest : public ::testing::Test
{
    protected:
    TransportControllerTest()
    {
    }
    void SetUp()
    {
    }

    void TearDown()
    {
    }
    sushi_controller::TransportServerMockup server;
    std::shared_ptr<sushi_controller::TransportController> controller = sushi_controller::CreateTransportController("localhost:51051");
};

TEST_F(TransportControllerTest, GetSampleRate)
{
    auto result = controller->get_samplerate();
    ASSERT_EQ(result.first, sushi_controller::ControlStatus::OK);
    ASSERT_FLOAT_EQ(result.second,sushi_controller::expected_results::SAMPLERATE);
}
TEST_F(TransportControllerTest, GetPlayingMode)
{
    auto result = controller->get_playing_mode();
    ASSERT_EQ(result.first, sushi_controller::ControlStatus::OK);
    ASSERT_EQ(result.second, sushi_controller::expected_results::PLAYING_MODE);
}

TEST_F(TransportControllerTest, SetPlayingMode)
{
    sushi_controller::ControlStatus status = controller->set_playing_mode(sushi_controller::PlayingMode::STOPPED);
    ASSERT_EQ(status, sushi_controller::ControlStatus::OK);
    ASSERT_EQ(controller->get_playing_mode().second,sushi_controller::PlayingMode::STOPPED);
    status = controller->set_playing_mode(sushi_controller::PlayingMode::PLAYING);
    ASSERT_EQ(status, sushi_controller::ControlStatus::OK);
    ASSERT_EQ(controller->get_playing_mode().second,sushi_controller::PlayingMode::PLAYING);
    status = controller->set_playing_mode(sushi_controller::PlayingMode::RECORDING);
    ASSERT_EQ(status, sushi_controller::ControlStatus::OK);
    ASSERT_EQ(controller->get_playing_mode().second,sushi_controller::PlayingMode::RECORDING);
}

TEST_F(TransportControllerTest, GetSyncMode)
{
    auto result = controller->get_sync_mode();
    ASSERT_EQ(result.first, sushi_controller::ControlStatus::OK);
    ASSERT_EQ(result.second, sushi_controller::expected_results::SYNC_MODE);
}

TEST_F(TransportControllerTest, SetSyncMode)
{
    sushi_controller::ControlStatus status = controller->set_sync_mode(sushi_controller::SyncMode::INTERNAL);
    ASSERT_EQ(status, sushi_controller::ControlStatus::OK);
    ASSERT_EQ(controller->get_sync_mode().second,sushi_controller::SyncMode::INTERNAL);
    status = controller->set_sync_mode(sushi_controller::SyncMode::MIDI);
    ASSERT_EQ(status, sushi_controller::ControlStatus::OK);
    ASSERT_EQ(controller->get_sync_mode().second,sushi_controller::SyncMode::MIDI);
    status = controller->set_sync_mode(sushi_controller::SyncMode::LINK);
    ASSERT_EQ(status, sushi_controller::ControlStatus::OK);
    ASSERT_EQ(controller->get_sync_mode().second,sushi_controller::SyncMode::LINK);
}

TEST_F(TransportControllerTest, GetTempo)
{
    auto result = controller->get_tempo();
    ASSERT_EQ(result.first, sushi_controller::ControlStatus::OK);
    ASSERT_FLOAT_EQ(result.second,sushi_controller::expected_results::TEMPO);
}

TEST_F(TransportControllerTest, SetTempoPositive)
{
    sushi_controller::ControlStatus status = controller->set_tempo(200.0f);
    ASSERT_EQ(status, sushi_controller::ControlStatus::OK);
    ASSERT_EQ(controller->get_tempo().second,200.0f);
}

TEST_F(TransportControllerTest, GetTimeSignature)
{
    auto result = controller->get_time_signature();
    ASSERT_EQ(result.first, sushi_controller::ControlStatus::OK);
    ASSERT_EQ(result.second.numerator,sushi_controller::expected_results::TIME_SIGNATURE.numerator);
    ASSERT_EQ(result.second.denominator,sushi_controller::expected_results::TIME_SIGNATURE.denominator);
}

TEST_F(TransportControllerTest, SetTimeSignature)
{
    sushi_controller::TimeSignature modified_time_signature{6,8};
    sushi_controller::ControlStatus status = controller->set_time_signature(modified_time_signature);
    ASSERT_EQ(status, sushi_controller::ControlStatus::OK);
    auto result = controller->get_time_signature();
    ASSERT_EQ(result.second.numerator, modified_time_signature.numerator);
    ASSERT_EQ(result.second.denominator, modified_time_signature.denominator);
}
