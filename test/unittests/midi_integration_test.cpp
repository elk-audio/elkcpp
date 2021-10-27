#include <gtest/gtest.h>

#include "sushi_client.h"
#include "midi_controller.cpp"
#include "test_utils/midi_server_mockup.h"
#define private public

class MidiControllerTest : public ::testing::Test
{
protected:
    ~MidiControllerTest()
    {

    }

    void SetUp()
    {

    }

    void TearDown()
    {

    }
    sushi_controller::MidiServerMockup server;
    std::shared_ptr<sushi_controller::MidiController> controller = sushi_controller::CreateMidiController("localhost:51051");
};

TEST_F(MidiControllerTest, GetInputPorts)
{
    auto result = controller->get_input_ports();
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result.first);
    ASSERT_EQ(sushi_controller::expected_results::MIDI_INPUT_PORTS, result.second);
}

TEST_F(MidiControllerTest, GetOutputPorts)
{
    auto result = controller->get_output_ports();
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result.first);
    ASSERT_EQ(sushi_controller::expected_results::MIDI_OUTPUT_PORTS, result.second);
}

TEST_F(MidiControllerTest, GetAllKbdInputConnections)
{
    auto result = controller->get_all_kbd_input_connections();
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result.first);
    ASSERT_EQ(sushi_controller::expected_results::KBD_CONNECTIONS, result.second);
}

TEST_F(MidiControllerTest, GetAllKbdOutputConnections)
{
    auto result = controller->get_all_kbd_output_connections();
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result.first);
    ASSERT_EQ(sushi_controller::expected_results::KBD_CONNECTIONS, result.second);
}

TEST_F(MidiControllerTest, GetAllCCInputConnections)
{
    auto result = controller->get_all_cc_input_connections();
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result.first);
    ASSERT_EQ(sushi_controller::expected_results::CC_CONNECTIONS, result.second);
}

TEST_F(MidiControllerTest, GetAllPCInputConnections)
{
    auto result = controller->get_all_pc_input_connections();
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result.first);
    ASSERT_EQ(sushi_controller::expected_results::PC_CONNECTIONS, result.second);
}


TEST_F(MidiControllerTest, GetCCInputConnectionsForProcessor)
{
    auto result = controller->get_cc_input_connections_for_processor(sushi_controller::expected_results::CC_CONNECTION.processor_id);
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result.first);
    ASSERT_EQ(sushi_controller::expected_results::CC_CONNECTIONS, result.second);
}

TEST_F(MidiControllerTest, GetPCInputConnectionsForProcessor)
{
    auto result = controller->get_pc_input_connections_for_processor(sushi_controller::expected_results::PC_CONNECTION.processor_id);
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result.first);
    ASSERT_EQ(sushi_controller::expected_results::PC_CONNECTIONS, result.second);
}

TEST_F(MidiControllerTest, ConnectKbdInputToTrack)
{
    auto result = controller->connect_kbd_input_to_track(sushi_controller::expected_results::KBD_CONNECTION);
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result);

    auto bad_arg = sushi_controller::expected_results::KBD_CONNECTION;
    bad_arg.port += 1;
    result = controller->connect_kbd_input_to_track(bad_arg);
    ASSERT_EQ(sushi_controller::ControlStatus::INVALID_ARGUMENTS, result);
}

TEST_F(MidiControllerTest, ConnectKbdOutputFromTrack)
{
    auto result = controller->connect_kbd_output_from_track(sushi_controller::expected_results::KBD_CONNECTION);
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result);

    auto bad_arg = sushi_controller::expected_results::KBD_CONNECTION;
    bad_arg.port += 1;
    result = controller->connect_kbd_output_from_track(bad_arg);
    ASSERT_EQ(sushi_controller::ControlStatus::INVALID_ARGUMENTS, result);
}

TEST_F(MidiControllerTest, ConnectCCToParameter)
{
    auto result = controller->connect_cc_to_parameter(sushi_controller::expected_results::CC_CONNECTION);
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result);

    auto bad_arg = sushi_controller::expected_results::CC_CONNECTION;
    bad_arg.parameter_id += 1;
    result = controller->connect_cc_to_parameter(bad_arg);
    ASSERT_EQ(sushi_controller::ControlStatus::INVALID_ARGUMENTS, result);
}

TEST_F(MidiControllerTest, ConnectPCToProcessor)
{
    auto result = controller->connect_pc_to_processor(sushi_controller::expected_results::PC_CONNECTION);
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result);

    auto bad_arg = sushi_controller::expected_results::PC_CONNECTION;
    bad_arg.processor_id += 1;
    result = controller->connect_pc_to_processor(bad_arg);
    ASSERT_EQ(sushi_controller::ControlStatus::INVALID_ARGUMENTS, result);
}

TEST_F(MidiControllerTest, DisconnectKbdInput)
{
    auto result = controller->disconnect_kbd_input(sushi_controller::expected_results::KBD_CONNECTION);
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result);

    auto bad_arg = sushi_controller::expected_results::KBD_CONNECTION;
    bad_arg.port += 1;
    result = controller->disconnect_kbd_input(bad_arg);
    ASSERT_EQ(sushi_controller::ControlStatus::INVALID_ARGUMENTS, result);
}

TEST_F(MidiControllerTest, DisconnectKbdOutput)
{
    auto result = controller->disconnect_kbd_output(sushi_controller::expected_results::KBD_CONNECTION);
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result);

    auto bad_arg = sushi_controller::expected_results::KBD_CONNECTION;
    bad_arg.port += 1;
    result = controller->disconnect_kbd_output(bad_arg);
    ASSERT_EQ(sushi_controller::ControlStatus::INVALID_ARGUMENTS, result);
}

TEST_F(MidiControllerTest, DisconnectCC)
{
    auto result = controller->disconnect_cc(sushi_controller::expected_results::CC_CONNECTION);
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result);

    auto bad_arg = sushi_controller::expected_results::CC_CONNECTION;
    bad_arg.parameter_id += 1;
    result = controller->disconnect_cc(bad_arg);
    ASSERT_EQ(sushi_controller::ControlStatus::INVALID_ARGUMENTS, result);
}

TEST_F(MidiControllerTest, DisconnectPC)
{
    auto result = controller->disconnect_pc(sushi_controller::expected_results::PC_CONNECTION);
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result);

    auto bad_arg = sushi_controller::expected_results::PC_CONNECTION;
    bad_arg.processor_id += 1;
    result = controller->disconnect_pc(bad_arg);
    ASSERT_EQ(sushi_controller::ControlStatus::INVALID_ARGUMENTS, result);
}

TEST_F(MidiControllerTest, DisconnectAllCCFromProcessor)
{
    auto result = controller->disconnect_all_cc_from_processor(sushi_controller::expected_results::CC_CONNECTION.processor_id);
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result);

    result = controller->disconnect_all_cc_from_processor(sushi_controller::expected_results::CC_CONNECTION.processor_id + 1);
    ASSERT_EQ(sushi_controller::ControlStatus::INVALID_ARGUMENTS, result);
}

TEST_F(MidiControllerTest, DisconnectAllPCFromProcessor)
{
    auto result = controller->disconnect_all_pc_from_processor(sushi_controller::expected_results::PC_CONNECTION.processor_id);
    ASSERT_EQ(sushi_controller::ControlStatus::OK, result);

    result = controller->disconnect_all_pc_from_processor(sushi_controller::expected_results::PC_CONNECTION.processor_id + 1);
    ASSERT_EQ(sushi_controller::ControlStatus::INVALID_ARGUMENTS, result);
}
