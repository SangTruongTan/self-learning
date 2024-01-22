#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <iostream>
#include <mutex>
#include <sstream>
#include <string>
#include <unordered_map>

#include "dlt/dlt.h"

/* DLT LOG */
#define LOG_DEFAULT(level, ...)                                                                    \
    Farm::Logger::getInstance().log_dlt(Farm::Logger::ModuleName::LOG_SRC_DEFAULT, level,          \
                                        __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)

#define LOG_ANIMAL(level, ...)                                                                     \
    Farm::Logger::getInstance().log_dlt(Farm::Logger::ModuleName::LOG_SRC_ANIMAL, level, __FILE__,         \
                                        __FUNCTION__, __LINE__, ##__VA_ARGS__)

#define LOG_USER(level, ...)                                                                       \
    Farm::Logger::getInstance().log_dlt(Farm::Logger::ModuleName::LOG_SRC_USER_INTERFACE, level,   \
                                        __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)

#define LOG_CLOCK(level, ...)                                                                      \
    Farm::Logger::getInstance().log_dlt(Farm::Logger::ModuleName::LOG_SRC_TIME_MANAGEMENT, level,  \
                                        __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)

#define LOG_FARM(level, ...)                                                                       \
    Farm::Logger::getInstance().log_dlt(Farm::Logger::ModuleName::LOG_SRC_MAC_DONALD, level,       \
                                        __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)

/* Console LOG */
#define LOG_CONSOLE(level, ...)                                                                    \
    Farm::Logger::getInstance().log_console(level, ##__VA_ARGS__)


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

    /**
     * @brief Construct a new Logger object
     *
     * @param AppId
     * @param ContextId
     */
    void setAppContext(std::string AppId, std::string ContextId);

    template <typename... Args> void log_dlt(ModuleName src, LogLevel level, Args... args) {
        if (level >= logLevel) {
            std::lock_guard<std::mutex> lock(this->mMutex);
            std::ostringstream ss = log_detailed(src, level, args...);
            DLT_LOG(this->ctx, dltLogLevel.at(level), DLT_CSTRING(ss.str().c_str()));
        }
    }

    template <typename... Args>
    void log_console(LogLevel level, Args... args) {
        if (level >= logLevel) {
            std::lock_guard<std::mutex> lock(this->mMutex);
            std::cout << log_simple(args...).str();
        }
    }

    template <typename... Args>
    std::ostringstream log_detailed(ModuleName src, LogLevel level, const char *file,
                                    const char *func, int line, Args... args) {

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

private:
    DLT_DECLARE_CONTEXT(ctx)
    LogLevel logLevel = INFO;

    Logger(const Logger &rhs);
    Logger &operator=(const Logger &rhs);

    template <typename T, typename... Args>
    void appendToStream(std::ostringstream &stream, T value, Args... args) {
        stream << value;                 // Append the current argument to the stream
        appendToStream(stream, args...); // Recursively append remaining arguments
    }

    void appendToStream(std::ostringstream & /*stream*/) {
        // Base case for the variadic template recursion
    }

    static const std::unordered_map<LogLevel, std::string> logLevelStrings;
    static const std::unordered_map<ModuleName, std::string> moduleNameStrings;
    static const std::unordered_map<LogLevel, DltLogLevelType> dltLogLevel;
    std::mutex mMutex;
};

} // namespace Farm

#endif // __LOGGER_H__
