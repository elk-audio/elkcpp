#include <gtest/gtest.h>

#include "sushi_client.h"
#include "cv_gate_controller.cpp"
#include "test_utils/cv_gate_server_mockup.h"
#define private public

class CvGateControllerTest : public ::testing::Test
{
protected:
    CvGateControllerTest()
    {

    }

    void SetUp()
    {

    }

    void TearDown()
    {

    }

    sushi_controller::CvGateServerMockup server;
    std::shared_ptr<sushi_controller::CvGateController> controller = sushi_controller::CreateCvGateController("localhost:51051");
};

TEST_F(CvGateControllerTest, GetCvInputPorts)
{
    auto result = controller->get_cv_input_channel_count();
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result.first);
    ASSERT_EQ(sushi_controller::expected_results::N_INPUT_PORTS, result.second);
}

TEST_F(CvGateControllerTest, GetCvOutputPorts)
{
    auto result = controller->get_cv_output_channel_count();
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result.first);
    ASSERT_EQ(sushi_controller::expected_results::N_OUTPUT_PORTS, result.second);
}

TEST_F(CvGateControllerTest, GetAllCvInputConnections)
{
    auto result = controller->get_all_cv_input_connections();
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result.first);
    ASSERT_EQ(sushi_controller::expected_results::CV_CONNECTIONS, result.second);
}

TEST_F(CvGateControllerTest, GetAllCvOutputConnections)
{
    auto result = controller->get_all_cv_output_connections();
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result.first);
    ASSERT_EQ(sushi_controller::expected_results::CV_CONNECTIONS, result.second);
}

TEST_F(CvGateControllerTest, GetAllGateInputConnections)
{
    auto result = controller->get_all_gate_input_connections();
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result.first);
    ASSERT_EQ(sushi_controller::expected_results::GATE_CONNECTIONS, result.second);
}

TEST_F(CvGateControllerTest, GetAllGateOutputConnections)
{
    auto result = controller->get_all_gate_output_connections();
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result.first);
    ASSERT_EQ(sushi_controller::expected_results::GATE_CONNECTIONS, result.second);
}

TEST_F(CvGateControllerTest, GetCvInputConnectionsForProcessor)
{
    auto result = controller->get_cv_input_connections_for_processor(sushi_controller::expected_results::CV_CONNECTION.processor_id);
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result.first);
    ASSERT_EQ(sushi_controller::expected_results::CV_CONNECTIONS, result.second);

    result = controller->get_cv_input_connections_for_processor(sushi_controller::expected_results::CV_CONNECTION.processor_id + 1);
    ASSERT_EQ(sushi_controller::ControlStatus::INVALID_ARGUMENTS, result.first);
}

TEST_F(CvGateControllerTest, GetCvOutputConnectionsForProcessor)
{
    auto result = controller->get_cv_output_connections_for_processor(sushi_controller::expected_results::CV_CONNECTION.processor_id);
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result.first);
    ASSERT_EQ(sushi_controller::expected_results::CV_CONNECTIONS, result.second);

    result = controller->get_cv_output_connections_for_processor(sushi_controller::expected_results::CV_CONNECTION.processor_id + 1);
    ASSERT_EQ(sushi_controller::ControlStatus::INVALID_ARGUMENTS, result.first);
}

TEST_F(CvGateControllerTest, GetGateInputConnectionsForProcessor)
{
    auto result = controller->get_gate_input_connections_for_processor(sushi_controller::expected_results::CV_CONNECTION.processor_id);
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result.first);
    ASSERT_EQ(sushi_controller::expected_results::GATE_CONNECTIONS, result.second);

    result = controller->get_gate_input_connections_for_processor(sushi_controller::expected_results::CV_CONNECTION.processor_id + 1);
    ASSERT_EQ(sushi_controller::ControlStatus::INVALID_ARGUMENTS, result.first);
}

TEST_F(CvGateControllerTest, GetGateOutputConnectionsForProcessor)
{
    auto result = controller->get_gate_output_connections_for_processor(sushi_controller::expected_results::CV_CONNECTION.processor_id);
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result.first);
    ASSERT_EQ(sushi_controller::expected_results::GATE_CONNECTIONS, result.second);

    result = controller->get_gate_output_connections_for_processor(sushi_controller::expected_results::CV_CONNECTION.processor_id + 1);
    ASSERT_EQ(sushi_controller::ControlStatus::INVALID_ARGUMENTS, result.first);
}

TEST_F(CvGateControllerTest, ConnectCvInputToParameter)
{
    auto result = controller->connect_cv_input_to_parameter(sushi_controller::expected_results::CV_CONNECTION.processor_id,
                                                            sushi_controller::expected_results::CV_CONNECTION.parameter_id,
                                                            sushi_controller::expected_results::CV_CONNECTION.cv_port_id);
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result);

    result = controller->connect_cv_input_to_parameter(sushi_controller::expected_results::CV_CONNECTION.processor_id + 1,
                                                       sushi_controller::expected_results::CV_CONNECTION.parameter_id - 1,
                                                       sushi_controller::expected_results::CV_CONNECTION.cv_port_id);
    ASSERT_EQ(sushi_controller::ControlStatus::INVALID_ARGUMENTS, result);
}

TEST_F(CvGateControllerTest, ConnectCvOutputFromParameter)
{
    auto result = controller->connect_cv_output_from_parameter(sushi_controller::expected_results::CV_CONNECTION.processor_id,
                                                               sushi_controller::expected_results::CV_CONNECTION.parameter_id,
                                                               sushi_controller::expected_results::CV_CONNECTION.cv_port_id);
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result);

    result = controller->connect_cv_output_from_parameter(sushi_controller::expected_results::CV_CONNECTION.processor_id + 1,
                                                          sushi_controller::expected_results::CV_CONNECTION.parameter_id - 1,
                                                          sushi_controller::expected_results::CV_CONNECTION.cv_port_id);
    ASSERT_EQ(sushi_controller::ControlStatus::INVALID_ARGUMENTS, result);
}

TEST_F(CvGateControllerTest, ConnectGateInputToProcessor)
{
    auto result = controller->connect_gate_input_to_processor(sushi_controller::expected_results::GATE_CONNECTION.processor_id,
                                                              sushi_controller::expected_results::GATE_CONNECTION.gate_port_id,
                                                              sushi_controller::expected_results::GATE_CONNECTION.channel,
                                                              sushi_controller::expected_results::GATE_CONNECTION.note_no);
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result);

    result = controller->connect_gate_input_to_processor(sushi_controller::expected_results::GATE_CONNECTION.processor_id + 1,
                                                         sushi_controller::expected_results::GATE_CONNECTION.gate_port_id - 1,
                                                         sushi_controller::expected_results::GATE_CONNECTION.channel,
                                                         sushi_controller::expected_results::GATE_CONNECTION.note_no);
    ASSERT_EQ(sushi_controller::ControlStatus::INVALID_ARGUMENTS, result);
}

TEST_F(CvGateControllerTest, ConnectGateOutputFromProcessor)
{
    auto result = controller->connect_gate_output_from_processor(sushi_controller::expected_results::GATE_CONNECTION.processor_id,
                                                              sushi_controller::expected_results::GATE_CONNECTION.gate_port_id,
                                                              sushi_controller::expected_results::GATE_CONNECTION.channel,
                                                              sushi_controller::expected_results::GATE_CONNECTION.note_no);
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result);

    result = controller->connect_gate_output_from_processor(sushi_controller::expected_results::GATE_CONNECTION.processor_id + 1,
                                                            sushi_controller::expected_results::GATE_CONNECTION.gate_port_id - 1,
                                                            sushi_controller::expected_results::GATE_CONNECTION.channel,
                                                            sushi_controller::expected_results::GATE_CONNECTION.note_no);
    ASSERT_EQ(sushi_controller::ControlStatus::INVALID_ARGUMENTS, result);
}

TEST_F(CvGateControllerTest, DisconnectCvInput)
{
    auto result = controller->disconnect_cv_input(sushi_controller::expected_results::CV_CONNECTION.processor_id,
                                                  sushi_controller::expected_results::CV_CONNECTION.parameter_id,
                                                  sushi_controller::expected_results::CV_CONNECTION.cv_port_id);
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result);

    result = controller->disconnect_cv_input(sushi_controller::expected_results::CV_CONNECTION.processor_id + 1,
                                              sushi_controller::expected_results::CV_CONNECTION.parameter_id - 1,
                                              sushi_controller::expected_results::CV_CONNECTION.cv_port_id);
    ASSERT_EQ(sushi_controller::ControlStatus::INVALID_ARGUMENTS, result);
}

TEST_F(CvGateControllerTest, DisconnectCvOutput)
{
    auto result = controller->disconnect_cv_output(sushi_controller::expected_results::CV_CONNECTION.processor_id,
                                                  sushi_controller::expected_results::CV_CONNECTION.parameter_id,
                                                  sushi_controller::expected_results::CV_CONNECTION.cv_port_id);
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result);

    result = controller->disconnect_cv_output(sushi_controller::expected_results::CV_CONNECTION.processor_id + 1,
                                              sushi_controller::expected_results::CV_CONNECTION.parameter_id - 1,
                                              sushi_controller::expected_results::CV_CONNECTION.cv_port_id);
    ASSERT_EQ(sushi_controller::ControlStatus::INVALID_ARGUMENTS, result);
}

TEST_F(CvGateControllerTest, DisconnectGateInput)
{
    auto result = controller->disconnect_gate_input(sushi_controller::expected_results::GATE_CONNECTION.processor_id,
                                                    sushi_controller::expected_results::GATE_CONNECTION.gate_port_id,
                                                    sushi_controller::expected_results::GATE_CONNECTION.channel,
                                                    sushi_controller::expected_results::GATE_CONNECTION.note_no);
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result);

    result = controller->disconnect_gate_input(sushi_controller::expected_results::GATE_CONNECTION.processor_id - 2,
                                                sushi_controller::expected_results::GATE_CONNECTION.gate_port_id + 1,
                                                sushi_controller::expected_results::GATE_CONNECTION.channel,
                                                sushi_controller::expected_results::GATE_CONNECTION.note_no);
    ASSERT_EQ(sushi_controller::ControlStatus::INVALID_ARGUMENTS, result);
}

TEST_F(CvGateControllerTest, DisconnectGateOutput)
{
    auto result = controller->disconnect_gate_output(sushi_controller::expected_results::GATE_CONNECTION.processor_id,
                                                     sushi_controller::expected_results::GATE_CONNECTION.gate_port_id,
                                                     sushi_controller::expected_results::GATE_CONNECTION.channel,
                                                     sushi_controller::expected_results::GATE_CONNECTION.note_no);
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result);

    result = controller->disconnect_gate_output(sushi_controller::expected_results::GATE_CONNECTION.processor_id + 5,
                                                sushi_controller::expected_results::GATE_CONNECTION.gate_port_id - 3,
                                                sushi_controller::expected_results::GATE_CONNECTION.channel,
                                                sushi_controller::expected_results::GATE_CONNECTION.note_no);
    ASSERT_EQ(sushi_controller::ControlStatus::INVALID_ARGUMENTS, result);
}

TEST_F(CvGateControllerTest, DisconnectAllCvInputsFromProcessor)
{
    auto result = controller->disconnect_all_cv_inputs_from_processor(sushi_controller::expected_results::CV_CONNECTION.processor_id);
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result);

    result = controller->disconnect_all_cv_inputs_from_processor(sushi_controller::expected_results::CV_CONNECTION.processor_id + 1);
    ASSERT_EQ(sushi_controller::ControlStatus::INVALID_ARGUMENTS, result);
}

TEST_F(CvGateControllerTest, DisconnectAllCvOutputsFromProcessor)
{
    auto result = controller->disconnect_all_cv_outputs_from_processor(sushi_controller::expected_results::CV_CONNECTION.processor_id);
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result);

    result = controller->disconnect_all_cv_outputs_from_processor(sushi_controller::expected_results::CV_CONNECTION.processor_id + 1);
    ASSERT_EQ(sushi_controller::ControlStatus::INVALID_ARGUMENTS, result);
}

TEST_F(CvGateControllerTest, DisconnectAllGateInputsFromProcessor)
{
    auto result = controller->disconnect_all_gate_inputs_from_processor(sushi_controller::expected_results::GATE_CONNECTION.processor_id);
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result);

    result = controller->disconnect_all_gate_inputs_from_processor(sushi_controller::expected_results::GATE_CONNECTION.processor_id + 1);
    ASSERT_EQ(sushi_controller::ControlStatus::INVALID_ARGUMENTS, result);
}

TEST_F(CvGateControllerTest, DisconnectAllGateOutputsFromProcessor)
{
    auto result = controller->disconnect_all_gate_outputs_from_processor(sushi_controller::expected_results::GATE_CONNECTION.processor_id);
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result);

    result = controller->disconnect_all_gate_outputs_from_processor(sushi_controller::expected_results::GATE_CONNECTION.processor_id + 1);
    ASSERT_EQ(sushi_controller::ControlStatus::INVALID_ARGUMENTS, result);
}