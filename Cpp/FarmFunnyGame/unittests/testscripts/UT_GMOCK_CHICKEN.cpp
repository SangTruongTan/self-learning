/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : UT_GMOCK_CHICKEN.cpp
 * @brief          : The GMock Test for the chicken class.
 ******************************************************************************
 * @attention
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2024 Sang Tan Truong
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include <gtest/gtest.h>

/* Standard libraries. */
#include <string>

/* Include source file. */
#include "Chicken.cxx"

/* Include other dependencies. */
#include "SharedObjects.h"

/* Include Fake and Mock files. */
#include "dlt/dlt_fake.h"

/* The fixture for testing a specific class or functionality -----------------*/
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

/* Test case(s) within the test suite ----------------------------------------*/
TEST_F(MyTestSuite, TestCase1) {
    // Test code and assertions for TestCase1
    EXPECT_EQ(2 + 2, 4);
    ASSERT_EQ(2 + 2, 4);
}

TEST_F(MyTestSuite, TestCase2) {
    // Test code and assertions for TestCase2
    EXPECT_NE(5, 10);
    ASSERT_NE(5, 10);
}

TEST_F(MyTestSuite, TestCase3) {
    // Test code and assertions for TestCase3
    EXPECT_EQ(2 * 2, 4);
    ASSERT_TRUE(true);
}

TEST_F(MyTestSuite, TestCase4) {
    Farm::SharedObjects shared;
    std::string name = "Chicken";
    Farm::Chicken *obj = new Farm::Chicken(name, shared);
    delete obj;
    obj = nullptr;
}
