/**
 ******************************************************************************
 * @file           : UT_GMOCK_Chicken.cpp
 * @brief          : The GMock Test for the chicken class.
 ******************************************************************************
 * @attention
 *
 * BSD 3-Clause License
 *
 * Copyright (c) 2024, Sang Tan Truong.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of Sang Tan Truong nor the names of its contributors may
 *    be used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
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
class ChickenTestSuite : public ::testing::Test {
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
TEST_F(ChickenTestSuite, TestCase1) {
    // Test code and assertions for TestCase1
    EXPECT_EQ(2 + 2, 4);
    ASSERT_EQ(2 + 2, 4);
}

TEST_F(ChickenTestSuite, TestCase2) {
    // Test code and assertions for TestCase2
    EXPECT_NE(5, 10);
    ASSERT_NE(5, 10);
}

TEST_F(ChickenTestSuite, TestCase3) {
    // Test code and assertions for TestCase3
    EXPECT_EQ(2 * 2, 4);
    ASSERT_TRUE(true);
}

TEST_F(ChickenTestSuite, TestCase4) {
    Farm::SharedObjects shared;
    std::string name = "Chicken";
    Farm::Chicken *obj = new Farm::Chicken(name, shared);
    delete obj;
    obj = nullptr;
}
