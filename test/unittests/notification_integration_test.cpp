#include <gtest/gtest.h>

#include "sushi_client.h"
#include "notification_controller.cpp"
#include "test_utils/notification_server_mockup.h"
#define private public


class NotificationControllerTest : public ::testing::Test
{
public:
    void transport_change_test_callback(sushi_controller::TransportUpdate update, sushi_controller::TransportUpdateType type)
    {
        static size_t iteration = 0;
        _transport_changes_callback_called = true;
        ASSERT_EQ(sushi_controller::expected_results::TRANSPORT_UPDATE_TYPES[iteration], type);
        ASSERT_EQ(sushi_controller::expected_results::TRANSPORT_UPDATE_CHANGES[iteration], update);
        if (iteration >= sushi_controller::expected_results::TRANSPORT_UPDATE_CHANGES.size())
        {
            FAIL();
        }
        iteration++;
    }

    void engine_cpu_timing_update_test_callback(sushi_controller::CpuTimings timings)
    {
        static size_t iteration = 0;
        _engine_cpu_timing_callback_called = true;
        ASSERT_EQ(sushi_controller::expected_results::TIMING_UPDATES[iteration], timings);
        if (iteration >= sushi_controller::expected_results::TIMING_UPDATES.size())
        {
            FAIL();
        }
        iteration++;
    }

    void track_changes_test_callback(sushi_controller::TrackUpdate update)
    {
        static size_t iteration = 0;
        _track_changes_callback_called = true;
        ASSERT_EQ(sushi_controller::expected_results::TRACK_UPDATES[iteration], update);
        if (iteration >= sushi_controller::expected_results::TRACK_UPDATES.size())
        {
            FAIL();
        }
        iteration++;
    }

    void processor_changes_test_callback(sushi_controller::ProcessorUpdate update)
    {
        static size_t iteration = 0;
        _processor_changes_callback_called = true;
        ASSERT_EQ(sushi_controller::expected_results::PROCESSOR_UPDATES[iteration], update);
        if (iteration >= sushi_controller::expected_results::PROCESSOR_UPDATES.size())
        {
            FAIL();
        }
        iteration++;
    }

    void parameter_update_test_callback(int processor_id, int parameter_id, float value)
    {
        static size_t iteration = 0;
        _parameter_update_callback_called = true;
        ASSERT_EQ(sushi_controller::expected_results::PROCESSOR_WITH_ID_2.id, processor_id);
        ASSERT_EQ(sushi_controller::expected_results::PARAMETER_WITH_ID_2.id, parameter_id);

        ASSERT_FLOAT_EQ(value , sushi_controller::expected_results::PARAMETER_CHANGE_VALUES[iteration]);
        if (iteration >= sushi_controller::expected_results::PARAMETER_CHANGE_VALUES.size())
        {
            FAIL();
        }
        iteration++;
    }

protected:
    NotificationControllerTest()
    {
    }
    void SetUp()
    {
    }

    void TearDown()
    {
    }

    sushi_controller::NotificationServerMockup server;
    std::shared_ptr<sushi_controller::NotificationController> controller = sushi_controller::CreateNotificationController("localhost:51051");
    bool _transport_changes_callback_called{false};
    bool _engine_cpu_timing_callback_called{false};
    bool _track_changes_callback_called{false};
    bool _processor_changes_callback_called{false};
    bool _parameter_update_callback_called{false};
};


TEST_F(NotificationControllerTest, SubscribeToTransportChanges)
{
    controller->subscribe_to_transport_changes(std::bind(&NotificationControllerTest::transport_change_test_callback,
                                                         this,
                                                         std::placeholders::_1,
                                                         std::placeholders::_2));
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    ASSERT_TRUE(_transport_changes_callback_called);
}

TEST_F(NotificationControllerTest, SubscribeToTrackChanges)
{
    controller->subscribe_to_track_changes(std::bind(&NotificationControllerTest::track_changes_test_callback,
                                                     this,
                                                     std::placeholders::_1));
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    ASSERT_TRUE(_track_changes_callback_called);
}

TEST_F(NotificationControllerTest, SubscribeToProcessorChanges)
{
    controller->subscribe_to_processor_changes(std::bind(&NotificationControllerTest::processor_changes_test_callback,
                                                     this,
                                                     std::placeholders::_1));
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    ASSERT_TRUE(_processor_changes_callback_called);
}

TEST_F(NotificationControllerTest, SubscribeToEngineCpuTimingUpdates)
{
    controller->subscribe_to_engine_cpu_timing_updates(std::bind(&NotificationControllerTest::engine_cpu_timing_update_test_callback,
                                                                 this,
                                                                 std::placeholders::_1));
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    ASSERT_TRUE(_engine_cpu_timing_callback_called);
}

// Should modify the mock server to able to poll if a subscribtion was started
TEST_F(NotificationControllerTest, SubscribeToParameterUpdates)
{
    std::vector<std::pair<int, int>> parameter_blacklist;
    parameter_blacklist.push_back({sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id,
                                   sushi_controller::expected_results::PARAMETER_WITH_ID_1.id});
    controller->subscribe_to_parameter_updates(std::bind(&NotificationControllerTest::parameter_update_test_callback,
                                                         this,
                                                         std::placeholders::_1,
                                                         std::placeholders::_2,
                                                         std::placeholders::_3),
                                               parameter_blacklist);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    ASSERT_TRUE(_parameter_update_callback_called);
}
