#include <gtest/gtest.h>

#include "sushi_client.h"
#include "timing_controller.cpp"
#include "test_utils/timing_server_mockup.h"
#define private public


class TimingControllerTest : public ::testing::Test
{
    protected:
    TimingControllerTest()
    {
    }
    void SetUp()
    {
    }

    void TearDown()
    {
    }
    sushi_controller::TimingServerMockup server;
    std::shared_ptr<sushi_controller::TimingController> controller = sushi_controller::CreateTimingController("localhost:51051");
};

TEST_F(TimingControllerTest, GetTimingsEnabled)
{
    auto result = controller->get_timings_enabled();
    ASSERT_EQ(result.first, sushi_controller::ControlStatus::OK);
    ASSERT_EQ(result.second, sushi_controller::expected_results::TIMINGS_ENABLED);
}

TEST_F(TimingControllerTest, SetTimingsEnabled)
{
    bool value_to_set = !sushi_controller::expected_results::TIMINGS_ENABLED;
    auto result = controller->set_timings_enabled(value_to_set);
    ASSERT_EQ(result, sushi_controller::ControlStatus::OK);
    auto result2 = controller->get_timings_enabled();
    ASSERT_EQ(result2.first, sushi_controller::ControlStatus::OK);
    ASSERT_EQ(result2.second, value_to_set);

    value_to_set = sushi_controller::expected_results::TIMINGS_ENABLED;
    result = controller->set_timings_enabled(value_to_set);
    ASSERT_EQ(result, sushi_controller::ControlStatus::OK);
    result2 = controller->get_timings_enabled();
    ASSERT_EQ(result2.first, sushi_controller::ControlStatus::OK);
    ASSERT_EQ(result2.second, value_to_set);
}

TEST_F(TimingControllerTest, GetEngineTimings)
{
    auto result = controller->get_engine_timings();
    ASSERT_EQ(result.first, sushi_controller::ControlStatus::OK);
    ASSERT_EQ(result.second.min, sushi_controller::expected_results::ENGINE_TIMINGS.min);
    ASSERT_EQ(result.second.max, sushi_controller::expected_results::ENGINE_TIMINGS.max);
    ASSERT_EQ(result.second.avg, sushi_controller::expected_results::ENGINE_TIMINGS.avg);
}

TEST_F(TimingControllerTest, GetTrackTimings)
{
    auto result = controller->get_track_timings(sushi_controller::expected_results::TRACK_WITH_ID_1.id);
    ASSERT_EQ(result.first, sushi_controller::ControlStatus::OK);
    ASSERT_EQ(result.second.min, sushi_controller::expected_results::TRACK_TIMINGS.min);
    ASSERT_EQ(result.second.max, sushi_controller::expected_results::TRACK_TIMINGS.max);
    ASSERT_EQ(result.second.avg, sushi_controller::expected_results::TRACK_TIMINGS.avg);
}

TEST_F(TimingControllerTest, GetProcessorTimings)
{
    auto result = controller->get_processor_timings(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id);
    ASSERT_EQ(result.first, sushi_controller::ControlStatus::OK);
    ASSERT_EQ(result.second.min, sushi_controller::expected_results::PROCESSOR_TIMINGS.min);
    ASSERT_EQ(result.second.max, sushi_controller::expected_results::PROCESSOR_TIMINGS.max);
    ASSERT_EQ(result.second.avg, sushi_controller::expected_results::PROCESSOR_TIMINGS.avg);
}

TEST_F(TimingControllerTest, ResetAllTimings)
{
    ASSERT_EQ(controller->reset_all_timings(),sushi_controller::ControlStatus::OK);
}

TEST_F(TimingControllerTest, ResetTrackTimings)
{
    ASSERT_EQ(controller->reset_track_timings(sushi_controller::expected_results::TRACK_WITH_ID_1.id),sushi_controller::ControlStatus::OK);
}

TEST_F(TimingControllerTest, ResetProcessorTimings)
{
    ASSERT_EQ(controller->reset_processor_timings(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id),sushi_controller::ControlStatus::OK);
}
