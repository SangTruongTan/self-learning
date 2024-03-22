/**
 ******************************************************************************
 * @file           : TimeManager.h
 * @brief          : TimeManager's header file.
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TIME_MANAGER_H__
#define __TIME_MANAGER_H__

/* Includes ------------------------------------------------------------------*/
#include <atomic>
#include <functional>
#include <vector>

#include "Logger.h"

/* Declarations --------------------------------------------------------------*/
namespace Farm {
class TimeManager {
private:
    bool mRunning;
    std::atomic<int> mHour;
    std::atomic<int> mDay;

public:
    static constexpr const int CONTINUOUS = -1;

    std::atomic<bool> mIsPoisonReceived;

    /**
     * @brief Construct a new Time Manager object
     */
    TimeManager();

    /**
     * @brief Destroy the Time Manager object
     *
     */
    ~TimeManager();

    void start(std::vector<std::pair<const int, std::function<void(void)>>>
                   &timeLists);

    int getHour(void);
};
};     // namespace Farm
#endif /* __TIME_MANAGER_H__ */
