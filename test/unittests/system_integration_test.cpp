#include <gtest/gtest.h>

#include "sushi_client.h"
#include "system_controller.cpp"
#include "test_utils/system_server_mockup.h"
#define private public


class SystemControllerTest : public ::testing::Test
{
protected:
    SystemControllerTest()
    {

    }
    void SetUp()
    {

    }

    void TearDown()
    {

    }
    sushi_controller::SystemServerMockup server;
    std::shared_ptr<sushi_controller::SystemController> controller = sushi_controller::CreateSystemController("localhost:51051");
};

TEST_F(SystemControllerTest, GetSushiVersion)
{
    auto result = controller->get_sushi_version();
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result.first);
    ASSERT_EQ(sushi_controller::expected_results::VERSION_STRING, result.second);
}

TEST_F(SystemControllerTest, GetBuildInfo)
{
    auto result = controller->get_build_info();
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result.first);
    ASSERT_EQ(sushi_controller::expected_results::BUILD_INFO, result.second);
}

TEST_F(SystemControllerTest, GetInputAudioChannelCount)
{
    auto result = controller->get_input_audio_channel_count();
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result.first);
    ASSERT_EQ(sushi_controller::expected_results::INPUT_AUDIO_CHANNELS, result.second);
}

TEST_F(SystemControllerTest, GetOutputAudioChannelCount)
{
    auto result = controller->get_output_audio_channel_count();
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result.first);
    ASSERT_EQ(sushi_controller::expected_results::OUTPUT_AUDIO_CHANNELS, result.second);
}
