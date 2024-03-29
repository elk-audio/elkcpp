#include <thread>
#include <unistd.h>

#include "gtest/gtest.h"

#include "sushi_client.h"
#include "sushi_grpc_client.cpp"
#include "test_utils/sushi_server_mockup.h"
#define private public

sushi_controller::SushiServerMockup server;












<<<<<<< HEAD
 
class SushiClientKeyboardControlTest : public ::testing::Test
{
    protected:
    SushiClientKeyboardControlTest()
    {
    }
    void SetUp()
    {
    }

    void TearDown()
    {
    }
    std::shared_ptr<sushi_controller::SushiControl> controller = sushi_controller::CreateSushiController("localhost:51051");
};

TEST_F(SushiClientKeyboardControlTest, SendNoteOn)
{
    sushi_controller::ControlStatus status = controller->send_note_on(sushi_controller::expected_results::MIDI_TRACK_ID,
                                                                     sushi_controller::expected_results::MIDI_CHANNEL,
                                                                     sushi_controller::expected_results::MIDI_NOTE,
                                                                     sushi_controller::expected_results::MIDI_VELOCITY);
    ASSERT_EQ(status, sushi_controller::ControlStatus::OK);
}


TEST_F(SushiClientKeyboardControlTest, SendNoteOff)
{
    sushi_controller::ControlStatus status = controller->send_note_off(sushi_controller::expected_results::MIDI_TRACK_ID,
                                                                      sushi_controller::expected_results::MIDI_CHANNEL,
                                                                      sushi_controller::expected_results::MIDI_NOTE,
                                                                      sushi_controller::expected_results::MIDI_VELOCITY);
    ASSERT_EQ(status, sushi_controller::ControlStatus::OK);
}

TEST_F(SushiClientKeyboardControlTest, SendNoteAftertouch)
{
    sushi_controller::ControlStatus status = controller->send_note_aftertouch(sushi_controller::expected_results::MIDI_TRACK_ID,
                                                                             sushi_controller::expected_results::MIDI_CHANNEL,
                                                                             sushi_controller::expected_results::MIDI_NOTE,
                                                                             sushi_controller::expected_results::MIDI_AFTERTOUCH);
    ASSERT_EQ(status, sushi_controller::ControlStatus::OK);
}

TEST_F(SushiClientKeyboardControlTest, SendAftertouch)
{
    sushi_controller::ControlStatus status = controller->send_aftertouch(sushi_controller::expected_results::MIDI_TRACK_ID,
                                                                        sushi_controller::expected_results::MIDI_CHANNEL,
                                                                        sushi_controller::expected_results::MIDI_AFTERTOUCH);
    ASSERT_EQ(status, sushi_controller::ControlStatus::OK);
}

TEST_F(SushiClientKeyboardControlTest, SendPitchBend)
{
    sushi_controller::ControlStatus status = controller->send_pitch_bend(sushi_controller::expected_results::MIDI_TRACK_ID,
                                                                        sushi_controller::expected_results::MIDI_CHANNEL,
                                                                        sushi_controller::expected_results::MIDI_PITCH_BEND);
    ASSERT_EQ(status, sushi_controller::ControlStatus::OK);
}

TEST_F(SushiClientKeyboardControlTest, SendModulation)
{
    sushi_controller::ControlStatus status = controller->send_modulation(sushi_controller::expected_results::MIDI_TRACK_ID,
                                                                        sushi_controller::expected_results::MIDI_CHANNEL,
                                                                        sushi_controller::expected_results::MIDI_MODULATION);
    ASSERT_EQ(status, sushi_controller::ControlStatus::OK);
}

class SushiClientCpuTimingsTest : public ::testing::Test
{
    protected:
    SushiClientCpuTimingsTest()
    {
    }
    void SetUp()
    {
    }

    void TearDown()
    {
    }
    std::shared_ptr<sushi_controller::SushiControl> controller = sushi_controller::CreateSushiController("localhost:51051");
};

TEST_F(SushiClientCpuTimingsTest, GetEngineTimings)
{
    std::pair<sushi_controller::ControlStatus, sushi_controller::CpuTimings> result = controller->get_engine_timings();
    ASSERT_EQ(result.first, sushi_controller::ControlStatus::OK);
    ASSERT_EQ(result.second.min, sushi_controller::expected_results::ENGINE_TIMINGS.min);
    ASSERT_EQ(result.second.max, sushi_controller::expected_results::ENGINE_TIMINGS.max);
    ASSERT_EQ(result.second.avg, sushi_controller::expected_results::ENGINE_TIMINGS.avg);
}

TEST_F(SushiClientCpuTimingsTest, GetTrackTimings)
{
    std::pair<sushi_controller::ControlStatus, sushi_controller::CpuTimings> result = controller->get_track_timings(sushi_controller::expected_results::TRACK_WITH_ID_1.id);
    ASSERT_EQ(result.first, sushi_controller::ControlStatus::OK);
    ASSERT_EQ(result.second.min, sushi_controller::expected_results::TRACK_TIMINGS.min);
    ASSERT_EQ(result.second.max, sushi_controller::expected_results::TRACK_TIMINGS.max);
    ASSERT_EQ(result.second.avg, sushi_controller::expected_results::TRACK_TIMINGS.avg);
}

TEST_F(SushiClientCpuTimingsTest, GetProcessorTimings)
{
    std::pair<sushi_controller::ControlStatus, sushi_controller::CpuTimings> result = controller->get_processor_timings(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id);
    ASSERT_EQ(result.first, sushi_controller::ControlStatus::OK);
    ASSERT_EQ(result.second.min, sushi_controller::expected_results::PROCESSOR_TIMINGS.min);
    ASSERT_EQ(result.second.max, sushi_controller::expected_results::PROCESSOR_TIMINGS.max);
    ASSERT_EQ(result.second.avg, sushi_controller::expected_results::PROCESSOR_TIMINGS.avg);
}

TEST_F(SushiClientCpuTimingsTest, ResetAllTimings)
{
    ASSERT_EQ(controller->reset_all_timings(),sushi_controller::ControlStatus::OK);
}

TEST_F(SushiClientCpuTimingsTest, ResetTrackTimings)
{
    ASSERT_EQ(controller->reset_track_timings(sushi_controller::expected_results::TRACK_WITH_ID_1.id),sushi_controller::ControlStatus::OK);
}

TEST_F(SushiClientCpuTimingsTest, ResetProcessorTimings)
{
    ASSERT_EQ(controller->reset_processor_timings(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id),sushi_controller::ControlStatus::OK);
}

class SushiClientTrackControlTest : public ::testing::Test
{
    protected:
    SushiClientTrackControlTest()
    {
    }
    void SetUp()
    {
    }

    void TearDown()
    {
    }
    std::shared_ptr<sushi_controller::SushiControl> controller = sushi_controller::CreateSushiController("localhost:51051");
};

TEST_F(SushiClientTrackControlTest, GetTrackId)
{
    std::pair<sushi_controller::ControlStatus, int> result = controller->get_track_id(sushi_controller::expected_results::TRACK_WITH_ID_1.name);
    ASSERT_EQ(result.first, sushi_controller::ControlStatus::OK);
    ASSERT_EQ(result.second, sushi_controller::expected_results::TRACK_WITH_ID_1.id);
}

TEST_F(SushiClientTrackControlTest, GetTrackInfo)
{
    std::pair<sushi_controller::ControlStatus, sushi_controller::TrackInfo> result = controller->get_track_info(sushi_controller::expected_results::TRACK_WITH_ID_1.id);
    ASSERT_EQ(result.first, sushi_controller::ControlStatus::OK);
    ASSERT_EQ(result.second.id, sushi_controller::expected_results::TRACK_WITH_ID_1.id);
    ASSERT_EQ(result.second.label, sushi_controller::expected_results::TRACK_WITH_ID_1.label);
    ASSERT_EQ(result.second.name, sushi_controller::expected_results::TRACK_WITH_ID_1.name);
    ASSERT_EQ(result.second.input_channels, sushi_controller::expected_results::TRACK_WITH_ID_1.input_channels);
    ASSERT_EQ(result.second.input_busses, sushi_controller::expected_results::TRACK_WITH_ID_1.input_busses);
    ASSERT_EQ(result.second.output_channels, sushi_controller::expected_results::TRACK_WITH_ID_1.output_channels);
    ASSERT_EQ(result.second.output_channels, sushi_controller::expected_results::TRACK_WITH_ID_1.output_channels);
    ASSERT_EQ(result.second.processor_count, sushi_controller::expected_results::TRACK_WITH_ID_1.processor_count);
}

TEST_F(SushiClientTrackControlTest, GetTrackProcessors)
{
    std::pair<sushi_controller::ControlStatus, std::vector<sushi_controller::ProcessorInfo>> result = controller->get_track_processors(sushi_controller::expected_results::TRACK_WITH_ID_1.id);
    ASSERT_EQ(result.first, sushi_controller::ControlStatus::OK);
    for (uint i = 0; i < sushi_controller::expected_results::PROCESSOR_INFO_LIST.size(); ++i)
    {
        ASSERT_EQ(result.second.at(i).id, sushi_controller::expected_results::PROCESSOR_INFO_LIST.at(i).id);
        ASSERT_EQ(result.second.at(i).label, sushi_controller::expected_results::PROCESSOR_INFO_LIST.at(i).label);
        ASSERT_EQ(result.second.at(i).name, sushi_controller::expected_results::PROCESSOR_INFO_LIST.at(i).name);
        ASSERT_EQ(result.second.at(i).parameter_count, sushi_controller::expected_results::PROCESSOR_INFO_LIST.at(i).parameter_count);
        ASSERT_EQ(result.second.at(i).program_count, sushi_controller::expected_results::PROCESSOR_INFO_LIST.at(i).program_count);
    }
}

TEST_F(SushiClientTrackControlTest, GetTrackParameters)
{
    std::pair<sushi_controller::ControlStatus, std::vector<sushi_controller::ParameterInfo>> result = controller->get_track_parameters (sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id);
    ASSERT_EQ(result.first, sushi_controller::ControlStatus::OK);
    for (uint i = 0; i < sushi_controller::expected_results::PARAMETER_INFO_LIST.size(); ++i)
    {
        ASSERT_EQ(result.second.at(i).id, sushi_controller::expected_results::PARAMETER_INFO_LIST.at(i).id);
        ASSERT_EQ(result.second.at(i).type, sushi_controller::expected_results::PARAMETER_INFO_LIST.at(i).type);
        ASSERT_EQ(result.second.at(i).label, sushi_controller::expected_results::PARAMETER_INFO_LIST.at(i).label);
        ASSERT_EQ(result.second.at(i).name, sushi_controller::expected_results::PARAMETER_INFO_LIST.at(i).name);
        ASSERT_EQ(result.second.at(i).unit, sushi_controller::expected_results::PARAMETER_INFO_LIST.at(i).unit);
        ASSERT_EQ(result.second.at(i).automatable, sushi_controller::expected_results::PARAMETER_INFO_LIST.at(i).automatable);
        ASSERT_EQ(result.second.at(i).min_domain_value, sushi_controller::expected_results::PARAMETER_INFO_LIST.at(i).min_domain_value);
        ASSERT_EQ(result.second.at(i).max_domain_value, sushi_controller::expected_results::PARAMETER_INFO_LIST.at(i).max_domain_value);
    }
}

class SushiClientProcessorControlTest : public ::testing::Test
{
    protected:
    SushiClientProcessorControlTest()
    {
    }
    void SetUp()
    {
    }

    void TearDown()
    {
    }
    std::shared_ptr<sushi_controller::SushiControl> controller = sushi_controller::CreateSushiController("localhost:51051");
};

TEST_F(SushiClientProcessorControlTest, GetProcessorId)
{
    std::pair<sushi_controller::ControlStatus, int> result = controller->get_processor_id(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.name);
    ASSERT_EQ(result.first, sushi_controller::ControlStatus::OK);
    ASSERT_EQ(result.second, sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id);
}

TEST_F(SushiClientProcessorControlTest, GetProcessorInfo)
{
    std::pair<sushi_controller::ControlStatus, sushi_controller::ProcessorInfo> result = controller->get_processor_info(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id);
    ASSERT_EQ(result.first, sushi_controller::ControlStatus::OK);
    ASSERT_EQ(result.second.id, sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id);
    ASSERT_EQ(result.second.label, sushi_controller::expected_results::PROCESSOR_WITH_ID_1.label);
    ASSERT_EQ(result.second.name, sushi_controller::expected_results::PROCESSOR_WITH_ID_1.name);
    ASSERT_EQ(result.second.program_count, sushi_controller::expected_results::PROCESSOR_WITH_ID_1.program_count);
    ASSERT_EQ(result.second.parameter_count, sushi_controller::expected_results::PROCESSOR_WITH_ID_1.parameter_count);
}

TEST_F(SushiClientProcessorControlTest, GetProcessorBybassState)
{
    std::pair<sushi_controller::ControlStatus, bool> result = controller->get_processor_bypass_state(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id);
    ASSERT_EQ(result.first, sushi_controller::ControlStatus::OK);
    ASSERT_EQ(result.second, sushi_controller::expected_results::PROCESSOR_BYPASS_STATE);
}

TEST_F(SushiClientProcessorControlTest, SetProcessorBypassState)
{
    ASSERT_EQ(controller->set_processor_bypass_state(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id,false), sushi_controller::ControlStatus::OK);
    ASSERT_EQ(controller->get_processor_bypass_state(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id).second,false);
    ASSERT_EQ(controller->set_processor_bypass_state(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id,true), sushi_controller::ControlStatus::OK);
    ASSERT_EQ(controller->get_processor_bypass_state(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id).second,true);
}

TEST_F(SushiClientProcessorControlTest, GetProcessorCurrentProgram)
{
    std::pair<sushi_controller::ControlStatus, int> result = controller->get_processor_current_program(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id);
    ASSERT_EQ(result.first, sushi_controller::ControlStatus::OK);
    ASSERT_EQ(result.second, sushi_controller::expected_results::PROGRAM_ID);
}

TEST_F(SushiClientProcessorControlTest, GetProcessorCurrentProgramName)
{
    std::pair<sushi_controller::ControlStatus, std::string> result = controller->get_processor_current_program_name(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id);
    ASSERT_EQ(result.first, sushi_controller::ControlStatus::OK);
    ASSERT_EQ(result.second, sushi_controller::expected_results::PROGRAM_NAME);
}

TEST_F(SushiClientProcessorControlTest, GetProcessorProgramName)
{
    std::pair<sushi_controller::ControlStatus, std::string> result = controller->get_processor_program_name(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id, 
                                                                                                           sushi_controller::expected_results::PROGRAM_ID);
    ASSERT_EQ(result.first, sushi_controller::ControlStatus::OK);
    ASSERT_EQ(result.second, sushi_controller::expected_results::PROGRAM_NAME);
}

TEST_F(SushiClientProcessorControlTest, GetProcessorPrograms)
{
    std::pair<sushi_controller::ControlStatus, std::vector<std::string>> result = controller->get_processor_programs(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id);
    ASSERT_EQ(result.first, sushi_controller::ControlStatus::OK);
    for (uint i = 0; i < result.second.size(); ++i)
    {
        ASSERT_EQ(result.second.at(i), sushi_controller::expected_results::PROGRAM_NAME);
    }
}

TEST_F(SushiClientProcessorControlTest, SetProcessorProgram)
{
    sushi_controller::ControlStatus result = controller->set_processor_program(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id, 
                                                                              sushi_controller::expected_results::PROGRAM_ID);
    ASSERT_EQ(result, sushi_controller::ControlStatus::OK);
}

TEST_F(SushiClientProcessorControlTest, GetProcessorParameters)
{
    std::pair<sushi_controller::ControlStatus, std::vector<sushi_controller::ParameterInfo>> result = controller->get_processor_parameters(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id);
    ASSERT_EQ(result.first, sushi_controller::ControlStatus::OK);
    for(uint i = 0; i < result.second.size(); ++i)
    {
        ASSERT_EQ(result.second.at(i).id, sushi_controller::expected_results::PARAMETER_INFO_LIST.at(i).id);
        ASSERT_EQ(result.second.at(i).type, sushi_controller::expected_results::PARAMETER_INFO_LIST.at(i).type);
        ASSERT_EQ(result.second.at(i).label, sushi_controller::expected_results::PARAMETER_INFO_LIST.at(i).label);
        ASSERT_EQ(result.second.at(i).name, sushi_controller::expected_results::PARAMETER_INFO_LIST.at(i).name);
        ASSERT_EQ(result.second.at(i).unit, sushi_controller::expected_results::PARAMETER_INFO_LIST.at(i).unit);
        ASSERT_EQ(result.second.at(i).automatable, sushi_controller::expected_results::PARAMETER_INFO_LIST.at(i).automatable);
        ASSERT_EQ(result.second.at(i).min_domain_value, sushi_controller::expected_results::PARAMETER_INFO_LIST.at(i).min_domain_value);
        ASSERT_EQ(result.second.at(i).max_domain_value, sushi_controller::expected_results::PARAMETER_INFO_LIST.at(i).max_domain_value);
    }   
}

class SushiClientParameterControlTest : public ::testing::Test
{
    protected:
    SushiClientParameterControlTest()
    {
    }
    void SetUp()
    {
    }

    void TearDown()
    {
    }
    std::shared_ptr<sushi_controller::SushiControl> controller = sushi_controller::CreateSushiController("localhost:51051");
};

TEST_F(SushiClientParameterControlTest, GetParameterId)
{
    std::pair<sushi_controller::ControlStatus, int> result = controller->get_parameter_id(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id, 
                                                                                         sushi_controller::expected_results::PARAMETER_WITH_ID_1.name);
    ASSERT_EQ(result.first, sushi_controller::ControlStatus::OK);
    ASSERT_EQ(result.second, sushi_controller::expected_results::PARAMETER_WITH_ID_1.id);
}

TEST_F(SushiClientParameterControlTest, GetParameterInfo)
{
    std::pair<sushi_controller::ControlStatus, sushi_controller::ParameterInfo> result = controller->get_parameter_info(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id, 
                                                                                                                       sushi_controller::expected_results::PARAMETER_WITH_ID_1.id);
    ASSERT_EQ(result.first, sushi_controller::ControlStatus::OK);
    ASSERT_EQ(result.second.id, sushi_controller::expected_results::PARAMETER_WITH_ID_1.id);
    ASSERT_EQ(result.second.type, sushi_controller::expected_results::PARAMETER_WITH_ID_1.type);
    ASSERT_EQ(result.second.label, sushi_controller::expected_results::PARAMETER_WITH_ID_1.label);
    ASSERT_EQ(result.second.name, sushi_controller::expected_results::PARAMETER_WITH_ID_1.name);
    ASSERT_EQ(result.second.unit, sushi_controller::expected_results::PARAMETER_WITH_ID_1.unit);
    ASSERT_EQ(result.second.automatable, sushi_controller::expected_results::PARAMETER_WITH_ID_1.automatable);
    ASSERT_EQ(result.second.min_domain_value, sushi_controller::expected_results::PARAMETER_WITH_ID_1.min_domain_value);
    ASSERT_EQ(result.second.max_domain_value, sushi_controller::expected_results::PARAMETER_WITH_ID_1.max_domain_value);
}

TEST_F(SushiClientParameterControlTest, GetParameterValue)
{
    std::pair<sushi_controller::ControlStatus, float> result = controller->get_parameter_value(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id, 
                                                                                              sushi_controller::expected_results::PARAMETER_WITH_ID_1.id);
    ASSERT_EQ(result.first, sushi_controller::ControlStatus::OK);
    ASSERT_EQ(result.second, sushi_controller::expected_results::PARAMETER_NORMALISED_VALUE);
}

TEST_F(SushiClientParameterControlTest, GetParameterValueInDomain)
{
    std::pair<sushi_controller::ControlStatus, float> result = controller->get_parameter_value_in_domain(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id,
                                                                                                         sushi_controller::expected_results::PARAMETER_WITH_ID_1.id);
    ASSERT_EQ(result.first, sushi_controller::ControlStatus::OK);
    ASSERT_EQ(result.second, sushi_controller::expected_results::PARAMETER_DOMAIN_VALUE);
}

TEST_F(SushiClientParameterControlTest, GetParameterValueAsString)
{
    std::pair<sushi_controller::ControlStatus, std::string> result = controller->get_parameter_value_as_string(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id, 
                                                                                                              sushi_controller::expected_results::PARAMETER_WITH_ID_1.id);
    ASSERT_EQ(result.first, sushi_controller::ControlStatus::OK);
    ASSERT_EQ(result.second, sushi_controller::expected_results::PARAMETER_STRING_VALUE);
}

TEST_F(SushiClientParameterControlTest, SetParameterValue)
{
    sushi_controller::ControlStatus result = controller->set_parameter_value(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id, 
                                                                             sushi_controller::expected_results::PARAMETER_WITH_ID_1.id,
                                                                             sushi_controller::expected_results::PARAMETER_DOMAIN_VALUE);
    ASSERT_EQ(result, sushi_controller::ControlStatus::OK);
}


=======
>>>>>>> develop

