#include <gtest/gtest.h>

#include "sushi_client.h"
#include "audio_graph_controller.cpp"
#include "test_utils/audio_graph_server_mockup.h"
#define private public


class AudioGraphControllerTest : public ::testing::Test
{
    protected:
    AudioGraphControllerTest()
    {
    }
    void SetUp()
    {
    }

    void TearDown()
    {
    }
    sushi_controller::AudioGraphServerMockup server;
    std::shared_ptr<sushi_controller::AudioGraphController> controller = sushi_controller::CreateAudioGraphController("localhost:51051");
};


TEST_F(AudioGraphControllerTest, GetAllTracks)
{
    std::pair<sushi_controller::ControlStatus, std::vector<sushi_controller::TrackInfo>> result = controller->get_all_tracks();
    ASSERT_EQ(result.first, sushi_controller::ControlStatus::OK);
    std::vector<sushi_controller::TrackInfo> track_info_list = result.second;
    for(uint i = 0; i < track_info_list.size(); ++i)
    {
        ASSERT_EQ(track_info_list.at(i).id,sushi_controller::expected_results::TRACK_INFO_LIST.at(i).id);
        ASSERT_EQ(track_info_list.at(i).label,sushi_controller::expected_results::TRACK_INFO_LIST.at(i).label);
        ASSERT_EQ(track_info_list.at(i).name,sushi_controller::expected_results::TRACK_INFO_LIST.at(i).name);
        ASSERT_EQ(track_info_list.at(i).input_channels,sushi_controller::expected_results::TRACK_INFO_LIST.at(i).input_channels);
        ASSERT_EQ(track_info_list.at(i).input_busses,sushi_controller::expected_results::TRACK_INFO_LIST.at(i).input_busses);
        ASSERT_EQ(track_info_list.at(i).output_channels,sushi_controller::expected_results::TRACK_INFO_LIST.at(i).output_channels);
        ASSERT_EQ(track_info_list.at(i).output_busses,sushi_controller::expected_results::TRACK_INFO_LIST.at(i).output_busses);
        ASSERT_EQ(track_info_list.at(i).processors,sushi_controller::expected_results::TRACK_INFO_LIST.at(i).processors);
    }
}

TEST_F(AudioGraphControllerTest, GetTrackId)
{
    std::pair<sushi_controller::ControlStatus, int> result = controller->get_track_id(sushi_controller::expected_results::TRACK_WITH_ID_1.name);
    ASSERT_EQ(result.first, sushi_controller::ControlStatus::OK);
    ASSERT_EQ(result.second, sushi_controller::expected_results::TRACK_WITH_ID_1.id);
}

TEST_F(AudioGraphControllerTest, GetTrackInfo)
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
    ASSERT_EQ(result.second.processors, sushi_controller::expected_results::TRACK_WITH_ID_1.processors);
}

TEST_F(AudioGraphControllerTest, GetTrackProcessors)
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

TEST_F(AudioGraphControllerTest, GetProcessorId)
{
    std::pair<sushi_controller::ControlStatus, int> result = controller->get_processor_id(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.name);
    ASSERT_EQ(result.first, sushi_controller::ControlStatus::OK);
    ASSERT_EQ(result.second, sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id);
}

TEST_F(AudioGraphControllerTest, GetProcessorInfo)
{
    std::pair<sushi_controller::ControlStatus, sushi_controller::ProcessorInfo> result = controller->get_processor_info(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id);
    ASSERT_EQ(result.first, sushi_controller::ControlStatus::OK);
    ASSERT_EQ(result.second.id, sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id);
    ASSERT_EQ(result.second.label, sushi_controller::expected_results::PROCESSOR_WITH_ID_1.label);
    ASSERT_EQ(result.second.name, sushi_controller::expected_results::PROCESSOR_WITH_ID_1.name);
    ASSERT_EQ(result.second.program_count, sushi_controller::expected_results::PROCESSOR_WITH_ID_1.program_count);
    ASSERT_EQ(result.second.parameter_count, sushi_controller::expected_results::PROCESSOR_WITH_ID_1.parameter_count);
}

TEST_F(AudioGraphControllerTest, GetProcessorBybassState)
{
    std::pair<sushi_controller::ControlStatus, bool> result = controller->get_processor_bypass_state(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id);
    ASSERT_EQ(result.first, sushi_controller::ControlStatus::OK);
    ASSERT_EQ(result.second, sushi_controller::expected_results::PROCESSOR_BYPASS_STATE);
}

TEST_F(AudioGraphControllerTest, SetProcessorBypassState)
{
    ASSERT_EQ(controller->set_processor_bypass_state(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id,false), sushi_controller::ControlStatus::OK);
    ASSERT_EQ(controller->get_processor_bypass_state(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id).second,false);
    ASSERT_EQ(controller->set_processor_bypass_state(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id,true), sushi_controller::ControlStatus::OK);
    ASSERT_EQ(controller->get_processor_bypass_state(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id).second,true);
}

TEST_F(AudioGraphControllerTest, CreateTrack)
{
    sushi_controller::ControlStatus result = controller->create_track(sushi_controller::expected_results::DYN_TRACK_NAME,
                                                                      sushi_controller::expected_results::DYN_TRACK_CHANNELS);
    ASSERT_EQ(result, sushi_controller::ControlStatus::OK);
    result = controller->create_track(sushi_controller::expected_results::DYN_TRACK_NAME,
                                      sushi_controller::expected_results::DYN_TRACK_CHANNELS + 1);
    ASSERT_EQ(result, sushi_controller::ControlStatus::INVALID_ARGUMENTS);
}

TEST_F(AudioGraphControllerTest, CreateMultibusTrack)
{
    sushi_controller::ControlStatus result = controller->create_multibus_track(sushi_controller::expected_results::DYN_TRACK_NAME,
                                                                               sushi_controller::expected_results::DYN_TRACK_OUTPUT_BUSSES,
                                                                               sushi_controller::expected_results::DYN_TRACK_INPUT_BUSSES);
    ASSERT_EQ(result, sushi_controller::ControlStatus::OK);
    result = controller->create_multibus_track(sushi_controller::expected_results::DYN_TRACK_NAME,
                                               sushi_controller::expected_results::DYN_TRACK_OUTPUT_BUSSES+1,
                                               sushi_controller::expected_results::DYN_TRACK_INPUT_BUSSES-1);
    ASSERT_EQ(result, sushi_controller::ControlStatus::INVALID_ARGUMENTS);
}

TEST_F(AudioGraphControllerTest, CreateProcessorOnTrack)
{
    sushi_controller::ControlStatus result = controller->create_processor_on_track(sushi_controller::expected_results::DYN_PROC_NAME,
                                                                                   sushi_controller::expected_results::DYN_PROC_UID,
                                                                                   sushi_controller::expected_results::DYN_PROC_PATH,
                                                                                   sushi_controller::expected_results::DYN_PROC_TYPE,
                                                                                   sushi_controller::expected_results::DYN_PROC_DST_TRACK,
                                                                                   sushi_controller::expected_results::DYN_PROC_BEFORE_PROC,
                                                                                   sushi_controller::expected_results::DYN_PROC_ADD_TO_BACK);
    ASSERT_EQ(result, sushi_controller::ControlStatus::OK);
    result = controller->create_processor_on_track(sushi_controller::expected_results::DYN_PROC_NAME,
                                                   sushi_controller::expected_results::DYN_PROC_UID,
                                                   sushi_controller::expected_results::DYN_PROC_PATH,
                                                   sushi_controller::expected_results::DYN_PROC_TYPE,
                                                   sushi_controller::expected_results::DYN_PROC_DST_TRACK+1,
                                                   sushi_controller::expected_results::DYN_PROC_BEFORE_PROC-1,
                                                   sushi_controller::expected_results::DYN_PROC_ADD_TO_BACK);
    ASSERT_EQ(result, sushi_controller::ControlStatus::INVALID_ARGUMENTS);
}

TEST_F(AudioGraphControllerTest, MoveProcessorOnTrack)
{
    sushi_controller::ControlStatus result = controller->move_processor_on_track(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id,
                                                                                 sushi_controller::expected_results::DYN_PROC_SRC_TRACK,
                                                                                 sushi_controller::expected_results::DYN_PROC_DST_TRACK,
                                                                                 sushi_controller::expected_results::DYN_PROC_BEFORE_PROC,
                                                                                 sushi_controller::expected_results::DYN_PROC_ADD_TO_BACK);
    ASSERT_EQ(result, sushi_controller::ControlStatus::OK);
    result = controller->move_processor_on_track(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id,
                                                 sushi_controller::expected_results::DYN_PROC_SRC_TRACK + 1,
                                                 sushi_controller::expected_results::DYN_PROC_DST_TRACK - 1,
                                                 sushi_controller::expected_results::DYN_PROC_BEFORE_PROC,
                                                 sushi_controller::expected_results::DYN_PROC_ADD_TO_BACK);
    ASSERT_EQ(result, sushi_controller::ControlStatus::INVALID_ARGUMENTS);
}

TEST_F(AudioGraphControllerTest, DeleteProcessorFromTrack)
{
    sushi_controller::ControlStatus result = controller->delete_processor_from_track(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id,
                                                                                     sushi_controller::expected_results::TRACK_WITH_ID_1.id);
    ASSERT_EQ(result, sushi_controller::ControlStatus::OK);
    result = controller->delete_processor_from_track(-1, -1);
    ASSERT_EQ(result, sushi_controller::ControlStatus::INVALID_ARGUMENTS);
}

TEST_F(AudioGraphControllerTest, DeleteTrack)
{
    sushi_controller::ControlStatus result = controller->delete_track(sushi_controller::expected_results::TRACK_WITH_ID_1.id);
    ASSERT_EQ(result, sushi_controller::ControlStatus::OK);
    result = controller->delete_track(-1);
    ASSERT_EQ(result, sushi_controller::ControlStatus::INVALID_ARGUMENTS);
}
