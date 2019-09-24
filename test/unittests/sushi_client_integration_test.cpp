#include <thread>
#include <unistd.h>

#include "gtest/gtest.h"


#include "sushi_grpc_client.h"
#include "test_utils/sushi_server_mockup.h"
#define private public


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
    sushi_controller::SushiServerMockup server;
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
    sushi_controller::SushiServerMockup server;
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