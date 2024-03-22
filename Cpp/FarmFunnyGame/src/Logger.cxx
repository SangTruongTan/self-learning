/**
 ******************************************************************************
 * @file           : Logger.cxx
 * @brief          : Logger's source file.
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
#include "Logger.h"

/* Definitions ---------------------------------------------------------------*/
namespace Farm {

Logger::Logger(void) {}

Logger::~Logger(void) {
    LOG_DEFAULT(Farm::LogLevel::INFO, "Deinitialize Logger module");
    deinitScreen();
    DLT_UNREGISTER_CONTEXT(ctx);
    DLT_UNREGISTER_APP();
}

Logger &Logger::getInstance() {
    static Logger instance{Logger()};
    return instance;
}

void Logger::setLogLevel(LogLevel level) { logLevel = level; }

void Logger::setAppContext(std::string AppId, std::string ContextId) {
    Logger &ins = Logger::getInstance();

    DLT_REGISTER_APP(AppId.c_str(), "New Application");
    DLT_REGISTER_CONTEXT(ins.ctx, ContextId.c_str(),
                         "Test Context for Logging");
    LOG_DEFAULT(Farm::LogLevel::INFO, "Initialized Logger module");
    initScreen();
}

void Logger::initScreen() {
    LOG_DEFAULT(LogLevel::INFO, "Initializing the Screen");
    initscr();
    cbreak();
    echo();
    input = newwin(1, COLS, LINES - 1, 0);
    output = newwin(LINES - 3, COLS / 2, 2, 0);
    clockWin = newwin(2, COLS / 2, 0, 0);
    dashboard = newwin(LINES - 1, COLS / 2, 0, COLS / 2);
    wmove(output, LINES - 2, 0); /* start at the bottom */
    scrollok(output, TRUE);
    scrollok(dashboard,TRUE);
    iBuffer = new char[1024];
}

void Logger::deinitScreen() {
    LOG_DEFAULT(LogLevel::INFO, "Deinitialize the Screen");
    endwin();
    delete[] iBuffer;
}

const char *Logger::getLine(std::string sInput) {
    std::lock_guard<std::mutex> lock(mInputMutex);
    mvwprintw(input, 0, 0, "%s", sInput.c_str());
    if (wgetnstr(input, iBuffer, COLS - 4) != OK) {
        return nullptr;
    }
    werase(input);

    return iBuffer;
}

void Logger::cleanDashboard(void) { werase(dashboard); }

void Logger::resetCursorDashboard(void) { wmove(dashboard, 0, 0); }

const std::unordered_map<LogLevel, std::string> Logger::logLevelStrings = {
    {Farm::LogLevel::VERBOSE, "VERBOSE"}, {Farm::LogLevel::DEBUG, "DEBUG"},
    {Farm::LogLevel::INFO, "INFO"},       {Farm::LogLevel::WARNING, "WARNING"},
    {Farm::LogLevel::ERROR, "ERROR"},     {Farm::LogLevel::FATAL, "FATAL"}};

const std::unordered_map<Logger::ModuleName, std::string>
    Logger::moduleNameStrings = {
        {Logger::ModuleName::LOG_SRC_ANIMAL, "ANIMAL"},
        {Logger::ModuleName::LOG_SRC_USER_INTERFACE, "USER"},
        {Logger::ModuleName::LOG_SRC_TIME_MANAGEMENT, "CLOCK"},
        {Logger::ModuleName::LOG_SRC_MAC_DONALD, "FARM"},
        {Logger::ModuleName::LOG_SRC_DEFAULT, "DEFAULT"}};

const std::unordered_map<LogLevel, DltLogLevelType> Logger::dltLogLevel = {
    {Farm::LogLevel::VERBOSE, DLT_LOG_VERBOSE},
    {Farm::LogLevel::DEBUG, DLT_LOG_DEBUG},
    {Farm::LogLevel::INFO, DLT_LOG_INFO},
    {Farm::LogLevel::WARNING, DLT_LOG_WARN},
    {Farm::LogLevel::ERROR, DLT_LOG_ERROR},
    {Farm::LogLevel::FATAL, DLT_LOG_FATAL},
};

} // namespace Farm
