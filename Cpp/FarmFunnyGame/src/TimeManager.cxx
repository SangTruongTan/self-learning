/**
 ******************************************************************************
 * @file           : TimeManager.cxx
 * @brief          : TimeManager's source file.
 ******************************************************************************
 * @attention
 *
 * Copyright 2024, Sang Tan Truong.
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
#include "TimeManager.h"

#include <chrono>
#include <sstream>
#include <thread>

/* Definitions ---------------------------------------------------------------*/
namespace Farm {
TimeManager::TimeManager()
    : mRunning(true), mHour(0), mDay(0), mIsPoisonReceived(false){};
TimeManager::~TimeManager() {}

void TimeManager::start(
    std::vector<std::pair<const int, std::function<void(void)>>> &timeLists) {
    while (this->mRunning == true) {

        if (mIsPoisonReceived == true) {
            LOG_CLOCK(LogLevel::INFO, "The poison signal received");
            break;
        }
        std::stringstream sstr{};
        sstr << "mDay=" << this->mDay << "; mHour=" << this->mHour << ":00  ";
        LOG_CLOCK_SCREEN(sstr.str().c_str());

        for (auto const &time : timeLists) {
            if (time.first == this->mHour) {
                time.second();
            } else if (time.first == TimeManager::CONTINUOUS) {
                time.second();
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        if (++mHour == 24) {
            this->mDay += 1;
            this->mHour = 0;
        }
    }
    LOG_CLOCK(LogLevel::INFO, "Exit TimeManager::start() thread");
}

int TimeManager::getHour(void) {
    return mHour;
}
} // namespace Farm
