#include <gtest/gtest.h>

#include "sushi_client.h"
#include "program_controller.cpp"
#include "test_utils/program_server_mockup.h"
#define private public


class ProgramControllerTest : public ::testing::Test
{
    protected:
    ProgramControllerTest()
    {
    }
    void SetUp()
    {
    }

    void TearDown()
    {
    }
    sushi_controller::ProgramServerMockup server;
    std::shared_ptr<sushi_controller::ProgramController> controller = sushi_controller::CreateProgramController("localhost:51051");
};

TEST_F(ProgramControllerTest, GetProcessorCurrentProgram)
{
    std::pair<sushi_controller::ControlStatus, int> result = controller->get_processor_current_program(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id);
    ASSERT_EQ(result.first, sushi_controller::ControlStatus::OK);
    ASSERT_EQ(result.second, sushi_controller::expected_results::PROGRAM_ID);
}

TEST_F(ProgramControllerTest, GetProcessorCurrentProgramName)
{
    std::pair<sushi_controller::ControlStatus, std::string> result = controller->get_processor_current_program_name(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id);
    ASSERT_EQ(result.first, sushi_controller::ControlStatus::OK);
    ASSERT_EQ(result.second, sushi_controller::expected_results::PROGRAM_NAME);
}

TEST_F(ProgramControllerTest, GetProcessorProgramName)
{
    std::pair<sushi_controller::ControlStatus, std::string> result = controller->get_processor_program_name(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id,
                                                                                                           sushi_controller::expected_results::PROGRAM_ID);
    ASSERT_EQ(result.first, sushi_controller::ControlStatus::OK);
    ASSERT_EQ(result.second, sushi_controller::expected_results::PROGRAM_NAME);
}

TEST_F(ProgramControllerTest, GetProcessorPrograms)
{
    std::pair<sushi_controller::ControlStatus, std::vector<std::string>> result = controller->get_processor_programs(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id);
    ASSERT_EQ(result.first, sushi_controller::ControlStatus::OK);
    for (uint i = 0; i < result.second.size(); ++i)
    {
        ASSERT_EQ(result.second.at(i), sushi_controller::expected_results::PROGRAM_NAME);
    }
}

TEST_F(ProgramControllerTest, SetProcessorProgram)
{
    sushi_controller::ControlStatus result = controller->set_processor_program(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id,
                                                                              sushi_controller::expected_results::PROGRAM_ID);
    ASSERT_EQ(result, sushi_controller::ControlStatus::OK);
}
