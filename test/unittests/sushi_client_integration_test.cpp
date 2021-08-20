#include <thread>
#include <unistd.h>

#include "gtest/gtest.h"

#include "sushi_client.h"
#include "sushi_grpc_client.cpp"
#include "test_utils/sushi_server_mockup.h"
#define private public

sushi_controller::SushiServerMockup server;












class SushiClientSubscribeToParameterTest : public ::testing::Test
{
    protected:
    SushiClientSubscribeToParameterTest()
    {
    }
    void SetUp()
    {
    }

    void TearDown()
    {
    }
    std::shared_ptr<sushi_controller::SushiController> controller = sushi_controller::CreateSushiController("localhost:51051");
};

void test_callback(int processor_id, int parameter_id, float value)
{
    static int iteration = 0;
    ASSERT_EQ(sushi_controller::expected_results::PROCESSOR_WITH_ID_2.id, processor_id);
    ASSERT_EQ(sushi_controller::expected_results::PARAMETER_WITH_ID_2.id, parameter_id);

    ASSERT_FLOAT_EQ(value , sushi_controller::expected_results::PARAMETER_CHANGE_VALUES[iteration]);
    iteration++;
}

// Should modify the mock server to able to poll if a subscribtion was started
TEST_F(SushiClientSubscribeToParameterTest, SubscribeTest)
{
    std::vector<std::pair<int, int>> parameter_blacklist;
    parameter_blacklist.push_back({sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id,
                                   sushi_controller::expected_results::PARAMETER_WITH_ID_1.id});
    controller->subscribe_to_parameter_notifications(test_callback, parameter_blacklist);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}
