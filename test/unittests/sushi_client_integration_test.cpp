#include "gtest/gtest.h"
#define private public


// A more complex test case where tests can be grouped
// And setup and teardown functions added.
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
};

TEST_F(SushiClientTest, SushiClient)
{
    EXPECT_FALSE(0);
}