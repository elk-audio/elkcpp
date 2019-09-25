#include <thread>
#include <unistd.h>

#include "gtest/gtest.h"


#include "sushi_grpc_client.h"
#include "test_utils/sushi_server_mockup.h"
#define private public

sushi_controller::SushiServerMockup server;

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
    sushi_controller::SushiControllerClient controller{"localhost:51051"};
};

TEST_F(SushiClientKeyboardControlTest, SendNoteOn)
{
    sushi_controller::ControlStatus status = controller.send_note_on(sushi_controller::expected_results::MIDI_TRACK_ID,
                                                                     sushi_controller::expected_results::MIDI_CHANNEL,
                                                                     sushi_controller::expected_results::MIDI_NOTE,
                                                                     sushi_controller::expected_results::MIDI_VELOCITY);
    ASSERT_EQ(status, sushi_controller::ControlStatus::OK);
}


TEST_F(SushiClientKeyboardControlTest, SendNoteOff)
{
    sushi_controller::ControlStatus status = controller.send_note_off(sushi_controller::expected_results::MIDI_TRACK_ID,
                                                                      sushi_controller::expected_results::MIDI_CHANNEL,
                                                                      sushi_controller::expected_results::MIDI_NOTE,
                                                                      sushi_controller::expected_results::MIDI_VELOCITY);
    ASSERT_EQ(status, sushi_controller::ControlStatus::OK);
}

TEST_F(SushiClientKeyboardControlTest, SendNoteAftertouch)
{
    sushi_controller::ControlStatus status = controller.send_note_aftertouch(sushi_controller::expected_results::MIDI_TRACK_ID,
                                                                             sushi_controller::expected_results::MIDI_CHANNEL,
                                                                             sushi_controller::expected_results::MIDI_NOTE,
                                                                             sushi_controller::expected_results::MIDI_AFTERTOUCH);
    ASSERT_EQ(status, sushi_controller::ControlStatus::OK);
}

TEST_F(SushiClientKeyboardControlTest, SendAftertouch)
{
    sushi_controller::ControlStatus status = controller.send_aftertouch(sushi_controller::expected_results::MIDI_TRACK_ID,
                                                                        sushi_controller::expected_results::MIDI_CHANNEL,
                                                                        sushi_controller::expected_results::MIDI_AFTERTOUCH);
    ASSERT_EQ(status, sushi_controller::ControlStatus::OK);
}

TEST_F(SushiClientKeyboardControlTest, SendPitchBend)
{
    sushi_controller::ControlStatus status = controller.send_pitch_bend(sushi_controller::expected_results::MIDI_TRACK_ID,
                                                                        sushi_controller::expected_results::MIDI_CHANNEL,
                                                                        sushi_controller::expected_results::MIDI_PITCH_BEND);
    ASSERT_EQ(status, sushi_controller::ControlStatus::OK);
}

TEST_F(SushiClientKeyboardControlTest, SendModulation)
{
    sushi_controller::ControlStatus status = controller.send_modulation(sushi_controller::expected_results::MIDI_TRACK_ID,
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
    sushi_controller::SushiControllerClient controller{"localhost:51051"};
};

TEST_F(SushiClientCpuTimingsTest, GetEngineTimings)
{
    std::pair<sushi_controller::ControlStatus, sushi_controller::CpuTimings> result = controller.get_engine_timings();
    ASSERT_EQ(result.first, sushi_controller::ControlStatus::OK);
    ASSERT_EQ(result.second.min, sushi_controller::expected_results::ENGINE_TIMINGS.min);
    ASSERT_EQ(result.second.max, sushi_controller::expected_results::ENGINE_TIMINGS.max);
    ASSERT_EQ(result.second.avg, sushi_controller::expected_results::ENGINE_TIMINGS.avg);
}

TEST_F(SushiClientCpuTimingsTest, GetTrackTimings)
{
    std::pair<sushi_controller::ControlStatus, sushi_controller::CpuTimings> result = controller.get_track_timings(sushi_controller::expected_results::TRACK_WITH_ID_1.id);
    ASSERT_EQ(result.first, sushi_controller::ControlStatus::OK);
    ASSERT_EQ(result.second.min, sushi_controller::expected_results::TRACK_TIMINGS.min);
    ASSERT_EQ(result.second.max, sushi_controller::expected_results::TRACK_TIMINGS.max);
    ASSERT_EQ(result.second.avg, sushi_controller::expected_results::TRACK_TIMINGS.avg);
}

TEST_F(SushiClientCpuTimingsTest, GetProcessorTimings)
{
    std::pair<sushi_controller::ControlStatus, sushi_controller::CpuTimings> result = controller.get_processor_timings(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id);
    ASSERT_EQ(result.first, sushi_controller::ControlStatus::OK);
    ASSERT_EQ(result.second.min, sushi_controller::expected_results::PROCESSOR_TIMINGS.min);
    ASSERT_EQ(result.second.max, sushi_controller::expected_results::PROCESSOR_TIMINGS.max);
    ASSERT_EQ(result.second.avg, sushi_controller::expected_results::PROCESSOR_TIMINGS.avg);
}

TEST_F(SushiClientCpuTimingsTest, ResetAllTimings)
{
    ASSERT_EQ(controller.reset_all_timings(),sushi_controller::ControlStatus::OK);
}

TEST_F(SushiClientCpuTimingsTest, ResetTrackTimings)
{
    ASSERT_EQ(controller.reset_track_timings(sushi_controller::expected_results::TRACK_WITH_ID_1.id),sushi_controller::ControlStatus::OK);
}

TEST_F(SushiClientCpuTimingsTest, ResetProcessorTimings)
{
    ASSERT_EQ(controller.reset_processor_timings(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id),sushi_controller::ControlStatus::OK);
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
    sushi_controller::SushiControllerClient controller{"localhost:51051"};
};

TEST_F(SushiClientTrackControlTest, GetTrackId)
{
    std::pair<sushi_controller::ControlStatus, int> result = controller.get_track_id(sushi_controller::expected_results::TRACK_WITH_ID_1.name);
    ASSERT_EQ(result.first, sushi_controller::ControlStatus::OK);
    ASSERT_EQ(result.second, sushi_controller::expected_results::TRACK_WITH_ID_1.id);
}

TEST_F(SushiClientTrackControlTest, GetTrackInfo)
{
    std::pair<sushi_controller::ControlStatus, sushi_controller::TrackInfo> result = controller.get_track_info(sushi_controller::expected_results::TRACK_WITH_ID_1.id);
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
    std::pair<sushi_controller::ControlStatus, std::vector<sushi_controller::ProcessorInfo>> result = controller.get_track_processors(sushi_controller::expected_results::TRACK_WITH_ID_1.id);
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
    std::pair<sushi_controller::ControlStatus, std::vector<sushi_controller::ParameterInfo>> result = controller.get_track_parameters (sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id);
    ASSERT_EQ(result.first, sushi_controller::ControlStatus::OK);
    for (uint i = 0; i < sushi_controller::expected_results::PARAMETER_INFO_LIST.size(); ++i)
    {
        ASSERT_EQ(result.second.at(i).id, sushi_controller::expected_results::PARAMETER_INFO_LIST.at(i).id);
        ASSERT_EQ(result.second.at(i).type, sushi_controller::expected_results::PARAMETER_INFO_LIST.at(i).type);
        ASSERT_EQ(result.second.at(i).label, sushi_controller::expected_results::PARAMETER_INFO_LIST.at(i).label);
        ASSERT_EQ(result.second.at(i).name, sushi_controller::expected_results::PARAMETER_INFO_LIST.at(i).name);
        ASSERT_EQ(result.second.at(i).unit, sushi_controller::expected_results::PARAMETER_INFO_LIST.at(i).unit);
        ASSERT_EQ(result.second.at(i).automatable, sushi_controller::expected_results::PARAMETER_INFO_LIST.at(i).automatable);
        ASSERT_EQ(result.second.at(i).min_range, sushi_controller::expected_results::PARAMETER_INFO_LIST.at(i).min_range);
        ASSERT_EQ(result.second.at(i).max_range, sushi_controller::expected_results::PARAMETER_INFO_LIST.at(i).max_range);
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
    sushi_controller::SushiControllerClient controller{"localhost:51051"};
};

TEST_F(SushiClientProcessorControlTest, GetProcessorId)
{
    std::pair<sushi_controller::ControlStatus, int> result = controller.get_processor_id(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.name);
    ASSERT_EQ(result.first, sushi_controller::ControlStatus::OK);
    ASSERT_EQ(result.second, sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id);
}

TEST_F(SushiClientProcessorControlTest, GetProcessorInfo)
{
    std::pair<sushi_controller::ControlStatus, sushi_controller::ProcessorInfo> result = controller.get_processor_info(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id);
    ASSERT_EQ(result.first, sushi_controller::ControlStatus::OK);
    ASSERT_EQ(result.second.id, sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id);
    ASSERT_EQ(result.second.label, sushi_controller::expected_results::PROCESSOR_WITH_ID_1.label);
    ASSERT_EQ(result.second.name, sushi_controller::expected_results::PROCESSOR_WITH_ID_1.name);
    ASSERT_EQ(result.second.program_count, sushi_controller::expected_results::PROCESSOR_WITH_ID_1.program_count);
    ASSERT_EQ(result.second.parameter_count, sushi_controller::expected_results::PROCESSOR_WITH_ID_1.parameter_count);
}

TEST_F(SushiClientProcessorControlTest, GetProcessorBybassState)
{
    std::pair<sushi_controller::ControlStatus, bool> result = controller.get_processor_bypass_state(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id);
    ASSERT_EQ(result.first, sushi_controller::ControlStatus::OK);
    ASSERT_EQ(result.second, sushi_controller::expected_results::PROCESSOR_BYPASS_STATE);
}

TEST_F(SushiClientProcessorControlTest, SetProcessorBypassState)
{
    ASSERT_EQ(controller.set_processor_bypass_state(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id,false), sushi_controller::ControlStatus::OK);
    ASSERT_EQ(controller.get_processor_bypass_state(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id).second,false);
    ASSERT_EQ(controller.set_processor_bypass_state(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id,true), sushi_controller::ControlStatus::OK);
    ASSERT_EQ(controller.get_processor_bypass_state(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id).second,true);
}

TEST_F(SushiClientProcessorControlTest, GetProcessorCurrentProgram)
{
    std::pair<sushi_controller::ControlStatus, int> result = controller.get_processor_current_program(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id);
    ASSERT_EQ(result.first, sushi_controller::ControlStatus::OK);
    ASSERT_EQ(result.second, sushi_controller::expected_results::PROGRAM_ID);
}

TEST_F(SushiClientProcessorControlTest, GetProcessorCurrentProgramName)
{
    std::pair<sushi_controller::ControlStatus, std::string> result = controller.get_processor_current_program_name(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id);
    ASSERT_EQ(result.first, sushi_controller::ControlStatus::OK);
    ASSERT_EQ(result.second, sushi_controller::expected_results::PROGRAM_NAME);
}

TEST_F(SushiClientProcessorControlTest, GetProcessorProgramName)
{
    std::pair<sushi_controller::ControlStatus, std::string> result = controller.get_processor_program_name(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id, sushi_controller::expected_results::PROGRAM_ID);
    ASSERT_EQ(result.first, sushi_controller::ControlStatus::OK);
    ASSERT_EQ(result.second, sushi_controller::expected_results::PROGRAM_NAME);
}

TEST_F(SushiClientProcessorControlTest, GetProcessorPrograms)
{
    std::pair<sushi_controller::ControlStatus, std::vector<std::string>> result = controller.get_processor_programs(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id);
    ASSERT_EQ(result.first, sushi_controller::ControlStatus::OK);
    for (uint i = 0; i < result.second.size(); ++i)
    {
        ASSERT_EQ(result.second.at(i), sushi_controller::expected_results::PROGRAM_NAME);
    }
}

TEST_F(SushiClientProcessorControlTest, SetProcessorProgram)
{
    sushi_controller::ControlStatus result = controller.set_processor_program(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id, sushi_controller::expected_results::PROGRAM_ID);
    ASSERT_EQ(result, sushi_controller::ControlStatus::OK);
}

TEST_F(SushiClientProcessorControlTest, GetProcessorParameters)
{
    std::pair<sushi_controller::ControlStatus, std::vector<sushi_controller::ParameterInfo>> result = controller.get_processor_parameters(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id);
    ASSERT_EQ(result.first, sushi_controller::ControlStatus::OK);
    for(uint i = 0; i < result.second.size(); ++i)
    {
        ASSERT_EQ(result.second.at(i).id, sushi_controller::expected_results::PARAMETER_INFO_LIST.at(i).id);
        ASSERT_EQ(result.second.at(i).type, sushi_controller::expected_results::PARAMETER_INFO_LIST.at(i).type);
        ASSERT_EQ(result.second.at(i).label, sushi_controller::expected_results::PARAMETER_INFO_LIST.at(i).label);
        ASSERT_EQ(result.second.at(i).name, sushi_controller::expected_results::PARAMETER_INFO_LIST.at(i).name);
        ASSERT_EQ(result.second.at(i).unit, sushi_controller::expected_results::PARAMETER_INFO_LIST.at(i).unit);
        ASSERT_EQ(result.second.at(i).automatable, sushi_controller::expected_results::PARAMETER_INFO_LIST.at(i).automatable);
        ASSERT_EQ(result.second.at(i).min_range, sushi_controller::expected_results::PARAMETER_INFO_LIST.at(i).min_range);
        ASSERT_EQ(result.second.at(i).max_range, sushi_controller::expected_results::PARAMETER_INFO_LIST.at(i).max_range);
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
    sushi_controller::SushiControllerClient controller{"localhost:51051"};
};

TEST_F(SushiClientParameterControlTest, GetParameterId)
{
    std::pair<sushi_controller::ControlStatus, int> result = controller.get_parameter_id(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id, sushi_controller::expected_results::PARAMETER_WITH_ID_1.name);
    ASSERT_EQ(result.first, sushi_controller::ControlStatus::OK);
    ASSERT_EQ(result.second, sushi_controller::expected_results::PARAMETER_WITH_ID_1.id);
}

TEST_F(SushiClientParameterControlTest, GetParameterInfo)
{
    std::pair<sushi_controller::ControlStatus, sushi_controller::ParameterInfo> result = controller.get_parameter_info(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id, sushi_controller::expected_results::PARAMETER_WITH_ID_1.id);
    ASSERT_EQ(result.first, sushi_controller::ControlStatus::OK);
    ASSERT_EQ(result.second.id, sushi_controller::expected_results::PARAMETER_WITH_ID_1.id);
    ASSERT_EQ(result.second.type, sushi_controller::expected_results::PARAMETER_WITH_ID_1.type);
    ASSERT_EQ(result.second.label, sushi_controller::expected_results::PARAMETER_WITH_ID_1.label);
    ASSERT_EQ(result.second.name, sushi_controller::expected_results::PARAMETER_WITH_ID_1.name);
    ASSERT_EQ(result.second.unit, sushi_controller::expected_results::PARAMETER_WITH_ID_1.unit);
    ASSERT_EQ(result.second.automatable, sushi_controller::expected_results::PARAMETER_WITH_ID_1.automatable);
    ASSERT_EQ(result.second.min_range, sushi_controller::expected_results::PARAMETER_WITH_ID_1.min_range);
    ASSERT_EQ(result.second.max_range, sushi_controller::expected_results::PARAMETER_WITH_ID_1.max_range);
}

TEST_F(SushiClientParameterControlTest, GetParameterValue)
{
    std::pair<sushi_controller::ControlStatus, float> result = controller.get_parameter_value(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id, sushi_controller::expected_results::PARAMETER_WITH_ID_1.id);
    ASSERT_EQ(result.first, sushi_controller::ControlStatus::OK);
    ASSERT_EQ(result.second, sushi_controller::expected_results::PARAMETER_VALUE);
}

TEST_F(SushiClientParameterControlTest, GetParameterValueNormalised)
{
    std::pair<sushi_controller::ControlStatus, float> result = controller.get_parameter_value_normalised(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id, sushi_controller::expected_results::PARAMETER_WITH_ID_1.id);
    ASSERT_EQ(result.first, sushi_controller::ControlStatus::OK);
    ASSERT_EQ(result.second, sushi_controller::expected_results::PARAMETER_NORMALISED_VALUE);
}

TEST_F(SushiClientParameterControlTest, GetParameterValueAsString)
{
    std::pair<sushi_controller::ControlStatus, std::string> result = controller.get_parameter_value_as_string(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id, sushi_controller::expected_results::PARAMETER_WITH_ID_1.id);
    ASSERT_EQ(result.first, sushi_controller::ControlStatus::OK);
    ASSERT_EQ(result.second, sushi_controller::expected_results::PARAMETER_STRING_VALUE);
}

TEST_F(SushiClientParameterControlTest, SetParameterValue)
{
    sushi_controller::ControlStatus result = controller.set_parameter_value(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id, sushi_controller::expected_results::PARAMETER_WITH_ID_1.id, sushi_controller::expected_results::PARAMETER_VALUE);
    ASSERT_EQ(result, sushi_controller::ControlStatus::OK);
}

TEST_F(SushiClientParameterControlTest, SetParameterValueNormalised)
{
    sushi_controller::ControlStatus result = controller.set_parameter_value_normalised(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id, sushi_controller::expected_results::PARAMETER_WITH_ID_1.id, sushi_controller::expected_results::PARAMETER_NORMALISED_VALUE);
    ASSERT_EQ(result, sushi_controller::ControlStatus::OK);
}