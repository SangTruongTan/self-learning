/**
 ******************************************************************************
 * @file           : UT_GMOCK_UserInterface.cpp
 * @brief          : The GMock Test for the UserInterface class.
 ******************************************************************************
 * @attention
 *
 * BSD 3-Clause License
 *
 * Copyright 2024, Sang Tan Truong
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the distribution.
 *
 * * Neither the name of Sang Tan Truong nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.
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
#include <mutex>
#include <string>

/* Include source file. */
#include "UserInterface.cxx"

/* Include other dependencies. */

/* Include Fake and Mock files. */
#include "dlt/dlt_fake.h"

/* The fixture for testing a specific class or functionality -----------------*/
class UserInterfaceTestSuite : public ::testing::Test {
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
TEST_F(UserInterfaceTestSuite, TestCase1) {
    std::mutex mtx;
    Farm::UserInterface *obj = new Farm::UserInterface(&mtx);
    delete obj;
    obj = nullptr;
}
