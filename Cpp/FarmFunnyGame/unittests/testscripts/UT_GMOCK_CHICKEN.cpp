#include <gtest/gtest.h>

// The fixture for testing a specific class or functionality
class MyTestSuite : public ::testing::Test {
protected:
    // Set up the test environment (optional)
    void SetUp() override {
        // Perform any necessary setup actions before each test case
    }

    // Tear down the test environment (optional)
    void TearDown() override {
        // Perform any necessary cleanup actions after each test case
    }
};

// Test case(s) within the test suite
TEST_F(MyTestSuite, TestCase1) {
    // Test code and assertions for TestCase1
    EXPECT_EQ(2 + 2, 4);
    ASSERT_TRUE(true);
}

TEST_F(MyTestSuite, TestCase2) {
    // Test code and assertions for TestCase2
    EXPECT_NE(5, 10);
    ASSERT_FALSE(false);
}
