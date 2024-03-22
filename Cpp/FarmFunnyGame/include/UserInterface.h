/**
 ******************************************************************************
 * @file           : UserInterface.h
 * @brief          : UserInterface's header file.
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
#ifndef __USER_INTERFACE_H__
#define __USER_INTERFACE_H__

/* Includes ------------------------------------------------------------------*/
#include <atomic>
#include <condition_variable>
#include <mutex>
#include <sstream>
#include <string>

#include "Logger.h"

/* Declarations --------------------------------------------------------------*/
namespace Farm {
class UserInterface {
private:
    std::string mUserInput;
    std::mutex *pMutex;

public:
    std::condition_variable mCV;
    std::istringstream mIss;

    std::atomic<bool> mIsPoisonReceived;

    UserInterface(std::mutex *Mutex);

    ~UserInterface();

    void start();
};
}; // namespace Farm

#endif /* __USER_INTERFACE_H__ */
