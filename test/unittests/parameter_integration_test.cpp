#include <gtest/gtest.h>

#include "sushi_client.h"
#include "parameter_controller.cpp"
#include "test_utils/parameter_server_mockup.h"
#define private public


class ParameterControllerTest : public ::testing::Test
{
    protected:
    ParameterControllerTest()
    {
    }
    void SetUp()
    {
    }

    void TearDown()
    {
    }
    sushi_controller::ParameterServerMockup server;
    std::shared_ptr<sushi_controller::ParameterController> controller = sushi_controller::CreateParameterController("localhost:51051");
};


TEST_F(ParameterControllerTest, GetTrackParameters)
{
    auto result = controller->get_track_parameters (sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id);
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

TEST_F(ParameterControllerTest, GetProcessorParameters)
{
    auto result = controller->get_processor_parameters(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id);
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

TEST_F(ParameterControllerTest, GetParameterId)
{
    auto result = controller->get_parameter_id(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id,
                                                                                         sushi_controller::expected_results::PARAMETER_WITH_ID_1.name);
    ASSERT_EQ(result.first, sushi_controller::ControlStatus::OK);
    ASSERT_EQ(result.second, sushi_controller::expected_results::PARAMETER_WITH_ID_1.id);
}

TEST_F(ParameterControllerTest, GetParameterInfo)
{
    auto result = controller->get_parameter_info(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id,
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

TEST_F(ParameterControllerTest, GetParameterValue)
{
    auto result = controller->get_parameter_value(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id,
                                                                                              sushi_controller::expected_results::PARAMETER_WITH_ID_1.id);
    ASSERT_EQ(result.first, sushi_controller::ControlStatus::OK);
    ASSERT_EQ(result.second, sushi_controller::expected_results::PARAMETER_VALUE);
}

TEST_F(ParameterControllerTest, GetParameterValueInDomain)
{
    auto result = controller->get_parameter_value_in_domain(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id,
                                                                                                         sushi_controller::expected_results::PARAMETER_WITH_ID_1.id);
    ASSERT_EQ(result.first, sushi_controller::ControlStatus::OK);
    ASSERT_EQ(result.second, sushi_controller::expected_results::PARAMETER_NORMALISED_VALUE);
}

TEST_F(ParameterControllerTest, GetParameterValueAsString)
{
    auto result = controller->get_parameter_value_as_string(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id,
                                                                                                              sushi_controller::expected_results::PARAMETER_WITH_ID_1.id);
    ASSERT_EQ(result.first, sushi_controller::ControlStatus::OK);
    ASSERT_EQ(result.second, sushi_controller::expected_results::PARAMETER_STRING_VALUE);
}

TEST_F(ParameterControllerTest, SetParameterValue)
{
    auto result = controller->set_parameter_value(sushi_controller::expected_results::PROCESSOR_WITH_ID_1.id,
                                                                            sushi_controller::expected_results::PARAMETER_WITH_ID_1.id,
                                                                            sushi_controller::expected_results::PARAMETER_VALUE);
    ASSERT_EQ(result, sushi_controller::ControlStatus::OK);
}
