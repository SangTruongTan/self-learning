/**
 ******************************************************************************
 * @file           : Logger.h
 * @brief          : Logger's header file.
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
#ifndef __LOGGER_H__
#define __LOGGER_H__

/* Includes ------------------------------------------------------------------*/
#include <chrono>
#include <iostream>
#include <mutex>
#include <sstream>
#include <stack>
#include <string>
#include <thread>
#include <unordered_map>

#include "curses.h"
#include "dlt/dlt.h"

/* DLT LOG */
#define LOG_DEFAULT(level, ...)                                                \
    Farm::Logger::getInstance().log_dlt(                                       \
        Farm::Logger::ModuleName::LOG_SRC_DEFAULT, level, __FILE__,            \
        __FUNCTION__, __LINE__, ##__VA_ARGS__)

#define LOG_ANIMAL(level, ...)                                                 \
    Farm::Logger::getInstance().log_dlt(                                       \
        Farm::Logger::ModuleName::LOG_SRC_ANIMAL, level, __FILE__,             \
        __FUNCTION__, __LINE__, ##__VA_ARGS__)

#define LOG_USER(level, ...)                                                   \
    Farm::Logger::getInstance().log_dlt(                                       \
        Farm::Logger::ModuleName::LOG_SRC_USER_INTERFACE, level, __FILE__,     \
        __FUNCTION__, __LINE__, ##__VA_ARGS__)

#define LOG_CLOCK(level, ...)                                                  \
    Farm::Logger::getInstance().log_dlt(                                       \
        Farm::Logger::ModuleName::LOG_SRC_TIME_MANAGEMENT, level, __FILE__,    \
        __FUNCTION__, __LINE__, ##__VA_ARGS__)

#define LOG_FARM(level, ...)                                                   \
    Farm::Logger::getInstance().log_dlt(                                       \
        Farm::Logger::ModuleName::LOG_SRC_MAC_DONALD, level, __FILE__,         \
        __FUNCTION__, __LINE__, ##__VA_ARGS__)

/* Console LOG */
#define LOG_CONSOLE(level, ...)                                                \
    Farm::Logger::getInstance().log_console(level, ##__VA_ARGS__)

/* Clock Output */
#define LOG_CLOCK_SCREEN(...)                                                  \
    Farm::Logger::getInstance().log_clock_screen(__VA_ARGS__)

/* Dash Board */
#define LOG_DASHBOARD(...)                                                     \
    Farm::Logger::getInstance().log_dashboard(__VA_ARGS__)

#define CLEAN_DASHBOARD() Farm::Logger::getInstance().cleanDashboard()

#define RESET_CURSOR_DASHBOARD()                                               \
    Farm::Logger::getInstance().resetCursorDashboard()

/* Get Line */
#define GET_LINE(msg) Logger::getInstance().getLine(msg)

/* Special Characters */
#define EOT_CHAR 0x04

/* Declarations --------------------------------------------------------------*/
namespace Farm {

/* Enum definition */
enum LogLevel { VERBOSE, DEBUG, INFO, WARNING, ERROR, FATAL };

class Logger {
public:
    enum ModuleName {
        LOG_SRC_ANIMAL,
        LOG_SRC_USER_INTERFACE,
        LOG_SRC_TIME_MANAGEMENT,
        LOG_SRC_MAC_DONALD,
        LOG_SRC_DEFAULT
    };

    Logger(void);

    ~Logger();

    static Logger &getInstance();

    void setLogLevel(LogLevel level);

    const char *getLine(std::string sInput);

    /**
     * @brief Construct a new Logger object
     *
     * @param AppId
     * @param ContextId
     */
    void setAppContext(std::string AppId, std::string ContextId);

    void cleanDashboard(void);

    void resetCursorDashboard(void);

    template <typename... Args>
    void log_dlt(ModuleName src, LogLevel level, Args... args) {
        if (level >= logLevel) {
            std::lock_guard<std::mutex> lock(this->mMutex);
            std::ostringstream ss = log_detailed(src, level, args...);
            DLT_LOG(this->ctx, dltLogLevel.at(level),
                    DLT_CSTRING(ss.str().c_str()));
        }
    }

    template <typename... Args> void log_console(LogLevel level, Args... args) {
        if (level >= logLevel) {
            std::lock_guard<std::mutex> lock(this->mMutex);
            int x = getcurx(input);
            int y = getcury(input);
            waddstr(output, log_simple(args...).str().c_str());
            wmove(input, y, x);
            wrefresh(output);
            wrefresh(input);
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }

    template <typename... Args>
    std::ostringstream log_detailed(ModuleName src, LogLevel level,
                                    const char *file, const char *func,
                                    int line, Args... args) {

        std::ostringstream logMessageStream;
        std::string moduleName = moduleNameStrings.at(src);
        logMessageStream << "[" << moduleName << "] ";
        logMessageStream << file << ":" << func << "():";
        logMessageStream << line << " ";

        std::string levelStr = logLevelStrings.at(level);
        logMessageStream << "[" << levelStr << "] => ";

        appendToStream(logMessageStream, args...);

        return logMessageStream;
    }

    template <typename... Args> std::ostringstream log_simple(Args... args) {

        std::ostringstream logMessageStream;

        appendToStream(logMessageStream, args...);

        return logMessageStream;
    }

    template <typename... Args> void log_clock_screen(Args... args) {
        std::lock_guard<std::mutex> lock(this->mMutex);
        int x = getcurx(input);
        int y = getcury(input);
        mvwprintw(clockWin, 0, 0, "%s", log_simple(args...).str().c_str());
        wmove(input, y, x);
        wrefresh(clockWin);
        wrefresh(input);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    template <typename... Args> void log_dashboard(Args... args) {
        std::lock_guard<std::mutex> lock(this->mMutex);
        int x = getcurx(input);
        int y = getcury(input);
        waddstr(dashboard, log_simple(args...).str().c_str());
        wmove(input, y, x);
        wrefresh(dashboard);
        wrefresh(input);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

private:
    DLT_DECLARE_CONTEXT(ctx)
    LogLevel logLevel = INFO;

    std::mutex mMutex;
    std::mutex mInputMutex;

    WINDOW *input;
    WINDOW *output;
    WINDOW *clockWin;
    WINDOW *dashboard;
    char *iBuffer;

    Logger(const Logger &rhs);
    Logger &operator=(const Logger &rhs);

    template <typename T, typename... Args>
    void appendToStream(std::ostringstream &stream, T value, Args... args) {
        stream << value; // Append the current argument to the stream
        appendToStream(stream,
                       args...); // Recursively append remaining arguments
    }

    void appendToStream(std::ostringstream & /*stream*/) {
        // Base case for the variadic template recursion
    }

    void initScreen();

    void deinitScreen();

    static const std::unordered_map<LogLevel, std::string> logLevelStrings;
    static const std::unordered_map<ModuleName, std::string> moduleNameStrings;
    static const std::unordered_map<LogLevel, DltLogLevelType> dltLogLevel;
};

} // namespace Farm

#endif // __LOGGER_H__
