/**
 ******************************************************************************
 * @file           : Logger_mock.hpp
 * @brief          : Logger's mock file.
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LOGGER_MOCK_H__
#define __LOGGER_MOCK_H__

/* Includes ------------------------------------------------------------------*/

/* Mock class defintions -----------------------------------------------------*/
class LoggerMock {
public:
    LoggerMock() {
        static Farm::Logger instance{Farm::Logger()};
        ON_CALL(*this, getInstance())
            .WillByDefault(::testing::ReturnRef(instance));
    }
    MOCK_METHOD0(getInstance, Farm::Logger &());
    MOCK_METHOD1(setLogLevel, void(Farm::LogLevel level));
    MOCK_METHOD1(getLine, const char *(std::string sInput));
    MOCK_METHOD2(setAppContext, void(std::string AppId, std::string ContextId));
    MOCK_METHOD0(cleanDashboard, void());
    MOCK_METHOD0(resetCursorDashboard, void());
    MOCK_METHOD0(initScreen, void());
    MOCK_METHOD0(deinitScreen, void());
};

/* Define Mock Object --------------------------------------------------------*/

LoggerMock *M_Logger{nullptr};

/* Mock Target defintions ----------------------------------------------------*/

Farm::Logger::Logger(void) {}

Farm::Logger::~Logger() {}

Farm::Logger &Farm::Logger::getInstance() { return M_Logger->getInstance(); }

void Farm::Logger::setLogLevel(LogLevel level) {
    return M_Logger->setLogLevel(level);
}

const char *Farm::Logger::getLine(std::string sInput) {
    return M_Logger->getLine(sInput);
}

void Farm::Logger::setAppContext(std::string AppId, std::string ContextId) {
    return M_Logger->setAppContext(AppId, ContextId);
}

void Farm::Logger::cleanDashboard(void) { return M_Logger->cleanDashboard(); }

void Farm::Logger::resetCursorDashboard(void) {
    return M_Logger->resetCursorDashboard();
}

void Farm::Logger::initScreen() { return M_Logger->initScreen(); }

void Farm::Logger::deinitScreen() { return M_Logger->deinitScreen(); }

Farm::Logger::Logger(const Logger &rhs) { this->input = rhs.input; }

Farm::Logger &Farm::Logger::operator=(const Logger &rhs) {
    this->input = rhs.input;
    return *this;
}

const std::unordered_map<Farm::LogLevel, std::string>
    Farm::Logger::logLevelStrings = {{Farm::LogLevel::VERBOSE, "VERBOSE"},
                                     {Farm::LogLevel::DEBUG, "DEBUG"},
                                     {Farm::LogLevel::INFO, "INFO"},
                                     {Farm::LogLevel::WARNING, "WARNING"},
                                     {Farm::LogLevel::ERROR, "ERROR"},
                                     {Farm::LogLevel::FATAL, "FATAL"}};

const std::unordered_map<Farm::Logger::ModuleName, std::string>
    Farm::Logger::moduleNameStrings = {
        {Logger::ModuleName::LOG_SRC_ANIMAL, "ANIMAL"},
        {Logger::ModuleName::LOG_SRC_USER_INTERFACE, "USER"},
        {Logger::ModuleName::LOG_SRC_TIME_MANAGEMENT, "CLOCK"},
        {Logger::ModuleName::LOG_SRC_MAC_DONALD, "FARM"},
        {Logger::ModuleName::LOG_SRC_DEFAULT, "DEFAULT"}};

const std::unordered_map<Farm::LogLevel, DltLogLevelType>
    Farm::Logger::dltLogLevel = {
        {Farm::LogLevel::VERBOSE, DLT_LOG_VERBOSE},
        {Farm::LogLevel::DEBUG, DLT_LOG_DEBUG},
        {Farm::LogLevel::INFO, DLT_LOG_INFO},
        {Farm::LogLevel::WARNING, DLT_LOG_WARN},
        {Farm::LogLevel::ERROR, DLT_LOG_ERROR},
        {Farm::LogLevel::FATAL, DLT_LOG_FATAL},
};

#endif /* __LOGGER_MOCK_H__ */