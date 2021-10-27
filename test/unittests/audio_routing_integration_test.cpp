#include <gtest/gtest.h>

#include "sushi_client.h"
#include "audio_routing_controller.cpp"
#include "test_utils/audio_routing_server_mockup.h"
#define private public

class AudioRoutingControllerTest : public ::testing::Test
{
protected:
    ~AudioRoutingControllerTest()
    {

    }

    void SetUp()
    {

    }

    void TearDown()
    {

    }
    sushi_controller::AudioRoutingServerMockup server;
    std::shared_ptr<sushi_controller::AudioRoutingController> controller = sushi_controller::CreateAudioRoutingController("localhost:51051");
};

TEST_F(AudioRoutingControllerTest, GetAllInputConnections)
{
    auto result = controller->get_all_input_connections();
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result.first);
    ASSERT_EQ(sushi_controller::expected_results::AUDIO_CONNECTIONS, result.second);
}

TEST_F(AudioRoutingControllerTest, GetAllOutputConnections)
{
    auto result = controller->get_all_output_connections();
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result.first);
    ASSERT_EQ(sushi_controller::expected_results::AUDIO_CONNECTIONS, result.second);
}

TEST_F(AudioRoutingControllerTest, GetInputConnectionsForTrack)
{
    auto result = controller->get_input_connections_for_track(sushi_controller::expected_results::AUDIO_CONNECTION.track_id);
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result.first);
    ASSERT_EQ(sushi_controller::expected_results::AUDIO_CONNECTIONS, result.second);

    result = controller->get_input_connections_for_track(sushi_controller::expected_results::AUDIO_CONNECTION.track_id + 1);
    ASSERT_EQ(sushi_controller::ControlStatus::INVALID_ARGUMENTS, result.first);
}

TEST_F(AudioRoutingControllerTest, GetOutputConnectionsForTrack)
{
    auto result = controller->get_output_connections_for_track(sushi_controller::expected_results::AUDIO_CONNECTION.track_id);
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result.first);
    ASSERT_EQ(sushi_controller::expected_results::AUDIO_CONNECTIONS, result.second);

    result = controller->get_output_connections_for_track(sushi_controller::expected_results::AUDIO_CONNECTION.track_id + 1);
    ASSERT_EQ(sushi_controller::ControlStatus::INVALID_ARGUMENTS, result.first);
}

TEST_F(AudioRoutingControllerTest, ConnectInputChannelToTrack)
{
    auto result = controller->connect_input_channel_to_track(sushi_controller::expected_results::AUDIO_CONNECTION);
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result);

    result = controller->connect_input_channel_to_track(sushi_controller::expected_results::AUDIO_CONNECTION.track_id,
                                                        sushi_controller::expected_results::AUDIO_CONNECTION.track_channel,
                                                        sushi_controller::expected_results::AUDIO_CONNECTION.engine_channel);
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result);

    result = controller->connect_input_channel_to_track(sushi_controller::expected_results::AUDIO_CONNECTION.track_id + 1,
                                                        sushi_controller::expected_results::AUDIO_CONNECTION.track_channel - 1,
                                                        sushi_controller::expected_results::AUDIO_CONNECTION.engine_channel);
    ASSERT_EQ(sushi_controller::ControlStatus::INVALID_ARGUMENTS, result);
}

TEST_F(AudioRoutingControllerTest, ConnectOutputChannelFromTrack)
{
    auto result = controller->connect_output_channel_from_track(sushi_controller::expected_results::AUDIO_CONNECTION);
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result);

    result = controller->connect_output_channel_from_track(sushi_controller::expected_results::AUDIO_CONNECTION.track_id,
                                                         sushi_controller::expected_results::AUDIO_CONNECTION.track_channel,
                                                         sushi_controller::expected_results::AUDIO_CONNECTION.engine_channel);
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result);

    result = controller->connect_output_channel_from_track(sushi_controller::expected_results::AUDIO_CONNECTION.track_id + 1,
                                                         sushi_controller::expected_results::AUDIO_CONNECTION.track_channel - 1,
                                                         sushi_controller::expected_results::AUDIO_CONNECTION.engine_channel);
    ASSERT_EQ(sushi_controller::ControlStatus::INVALID_ARGUMENTS, result);
}

TEST_F(AudioRoutingControllerTest, DisconnectInput)
{
    auto result = controller->disconnect_input(sushi_controller::expected_results::AUDIO_CONNECTION);
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result);

    result = controller->disconnect_input(sushi_controller::expected_results::AUDIO_CONNECTION.track_id,
                                          sushi_controller::expected_results::AUDIO_CONNECTION.track_channel,
                                          sushi_controller::expected_results::AUDIO_CONNECTION.engine_channel);
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result);

    result = controller->disconnect_input(sushi_controller::expected_results::AUDIO_CONNECTION.track_id + 1,
                                          sushi_controller::expected_results::AUDIO_CONNECTION.track_channel - 1,
                                          sushi_controller::expected_results::AUDIO_CONNECTION.engine_channel);
    ASSERT_EQ(sushi_controller::ControlStatus::INVALID_ARGUMENTS, result);
}

TEST_F(AudioRoutingControllerTest, DisconnectOutput)
{
    auto result = controller->disconnect_output(sushi_controller::expected_results::AUDIO_CONNECTION);
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result);

    result = controller->disconnect_output(sushi_controller::expected_results::AUDIO_CONNECTION.track_id,
                                           sushi_controller::expected_results::AUDIO_CONNECTION.track_channel,
                                           sushi_controller::expected_results::AUDIO_CONNECTION.engine_channel);
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result);

    result = controller->disconnect_output(sushi_controller::expected_results::AUDIO_CONNECTION.track_id + 1,
                                           sushi_controller::expected_results::AUDIO_CONNECTION.track_channel - 1,
                                           sushi_controller::expected_results::AUDIO_CONNECTION.engine_channel);
    ASSERT_EQ(sushi_controller::ControlStatus::INVALID_ARGUMENTS, result);
}

TEST_F(AudioRoutingControllerTest, DisconnectAllInputsFromTrack)
{
    auto result = controller->disconnect_all_inputs_from_track(sushi_controller::expected_results::AUDIO_CONNECTION.track_id);
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result);

    result = controller->disconnect_all_inputs_from_track(sushi_controller::expected_results::AUDIO_CONNECTION.track_id + 1);
    ASSERT_EQ(sushi_controller::ControlStatus::INVALID_ARGUMENTS, result);
}

TEST_F(AudioRoutingControllerTest, DisconnectAllOutputsFromTrack)
{
    auto result = controller->disconnect_all_outputs_from_track(sushi_controller::expected_results::AUDIO_CONNECTION.track_id);
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result);

    result = controller->disconnect_all_outputs_from_track(sushi_controller::expected_results::AUDIO_CONNECTION.track_id + 1);
    ASSERT_EQ(sushi_controller::ControlStatus::INVALID_ARGUMENTS, result);
}
