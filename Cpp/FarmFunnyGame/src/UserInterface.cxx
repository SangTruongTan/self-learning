/**
 ******************************************************************************
 * @file           : UserInterface.cxx
 * @brief          : UserInterface's source file.
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
#include "UserInterface.h"

#include <iostream>

/* Definitions ---------------------------------------------------------------*/
namespace Farm {

UserInterface::UserInterface(std::mutex *Mutex)
    : pMutex(Mutex), mIsPoisonReceived(false) {
    LOG_USER(LogLevel::INFO, "Initiated User Interface class");
}

UserInterface::~UserInterface() {
    LOG_USER(LogLevel::INFO, "De-initiated User Interface class");
}

void UserInterface::start() {
    LOG_USER(LogLevel::INFO, "Enter UserInterface::start()");
    while (true) {
        std::unique_lock<std::mutex> lock(*this->pMutex);
        this->mCV.wait(lock, [this] { return this->mIss.peek() == EOF; });
        const char *userInput = GET_LINE("Please type your commands: ");
        if (userInput == nullptr) {
            LOG_USER(LogLevel::ERROR, "Failed to get user input");
            continue;
        }
        this->mIss.clear();
        this->mIss.str(userInput);
        std::stringstream ss{};

        ss << "User Input is: " << userInput;
        LOG_USER(LogLevel::DEBUG, ss.str().c_str());

        this->mCV.notify_one();
        if ((mIsPoisonReceived = ((*userInput) == EOT_CHAR))) {
            LOG_USER(LogLevel::INFO, "Poison signal received");
            break;
        }
    }
    LOG_USER(LogLevel::INFO, "Exit UserInterface::start() thread");
}
} // namespace Farm
