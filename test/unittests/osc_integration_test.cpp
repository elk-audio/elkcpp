#include <gtest/gtest.h>

#include "sushi_client.h"
#include "osc_controller.cpp"
#include "test_utils/osc_server_mockup.h"
#define private public


class OscControllerTest : public ::testing::Test
{
protected:
    OscControllerTest()
    {

    }

    void SetUp()
    {

    }

    void TearDown()
    {

    }
    sushi_controller::OscServerMockup server;
    std::shared_ptr<sushi_controller::OscController> controller = sushi_controller::CreateOscController("localhost:51051");
};

TEST_F(OscControllerTest, GetSendPort)
{
    auto result = controller->get_send_port();
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result.first);
    ASSERT_EQ(sushi_controller::expected_results::SEND_PORT, result.second);
}

TEST_F(OscControllerTest, GetReceivePort)
{
    auto result = controller->get_receive_port();
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result.first);
    ASSERT_EQ(sushi_controller::expected_results::RECV_PORT, result.second);
}

TEST_F(OscControllerTest, GetEnabledParameterOutputs)
{
    auto result = controller->get_enabled_parameter_outputs();
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result.first);
    ASSERT_EQ(sushi_controller::expected_results::OSC_PATHS, result.second);
}

TEST_F(OscControllerTest, EnableOutputForParameter)
{
    auto result = controller->enable_output_for_parameter(sushi_controller::expected_results::PROCESSOR_ID,
                                                          sushi_controller::expected_results::PARAMETER_ID);
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result);

    result = controller->enable_output_for_parameter(sushi_controller::expected_results::PROCESSOR_ID + 1,
                                                     sushi_controller::expected_results::PARAMETER_ID);
    ASSERT_EQ(sushi_controller::ControlStatus::INVALID_ARGUMENTS, result);
}

TEST_F(OscControllerTest, DisableOutputForParameter)
{
    auto result = controller->disable_output_for_parameter(sushi_controller::expected_results::PROCESSOR_ID,
                                                           sushi_controller::expected_results::PARAMETER_ID);
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result);

    result = controller->disable_output_for_parameter(sushi_controller::expected_results::PROCESSOR_ID + 1,
                                                      sushi_controller::expected_results::PARAMETER_ID);
    ASSERT_EQ(sushi_controller::ControlStatus::INVALID_ARGUMENTS, result);
}

TEST_F(OscControllerTest, EnableAllOutput)
{
    auto result = controller->enable_all_output();
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result);
}

TEST_F(OscControllerTest, DisableAllOutput)
{
    auto result = controller->disable_all_output();
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result);
}