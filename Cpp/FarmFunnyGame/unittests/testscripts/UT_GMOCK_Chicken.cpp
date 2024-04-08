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
#include <gmock/gmock.h>
#include <gtest/gtest.h>

/* Standard libraries. */
#include <string>

/* Include source file. */
#include "Chicken.cxx"

/* Include other dependencies. */
#include "SharedObjects.h"

/* Include Fake and Mock files. */
#include "dlt/dlt_fake.h"

/* Include Mock classes.*/
#include "mock/Animal_mock.hpp"
#include "mock/Logger_mock.hpp"

/* The fixture for testing a specific class or functionality -----------------*/
class ChickenTestSuite : public ::testing::Test {
protected:
    // Set up the test environment (optional)
    void SetUp() override {
        // Perform any necessary setup actions before each test case
        M_Animal = new ::testing::NiceMock<AnimalMock>();
        M_Logger = new ::testing::NiceMock<LoggerMock>();
    }

    // Tear down the test environment (optional)
    void TearDown() override {
        // Perform any necessary cleanup actions after each test case
        delete static_cast<::testing::NiceMock<AnimalMock> *>(M_Animal);
        delete static_cast<::testing::NiceMock<LoggerMock> *>(M_Logger);
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

TEST_F(ChickenTestSuite, Contructor001) {
    Farm::SharedObjects shared;
    std::string name = "Chicken";
    Farm::Chicken *obj = new Farm::Chicken(name, shared);
    delete obj;
    obj = nullptr;
}

TEST_F(ChickenTestSuite, ExccedLifeTime001) {
    Farm::SharedObjects shared;
    std::string name = "Chicken";
    Farm::Chicken *obj = new Farm::Chicken(name, shared);
    EXPECT_CALL(*M_Animal, getAge())
        .WillOnce(::testing::Return(Farm::Animal::CHICKEN_LIFE_TIME));
    bool retval = obj->exceedLifeTime();
    EXPECT_TRUE(retval);
    delete obj;
    obj = nullptr;
}

TEST_F(ChickenTestSuite, ExccedLifeTime002) {
    Farm::SharedObjects shared;
    std::string name = "Chicken";
    Farm::Chicken *obj = new Farm::Chicken(name, shared);
    EXPECT_CALL(*M_Animal, getAge())
        .WillOnce(::testing::Return(Farm::Animal::CHICKEN_LIFE_TIME - 1));
    bool retval = obj->exceedLifeTime();
    EXPECT_FALSE(retval);
    delete obj;
    obj = nullptr;
}
