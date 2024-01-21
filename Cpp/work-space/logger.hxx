#ifndef LOGGER_HXX
#define LOGGER_HXX

#include <iostream>
#include <mutex>
#include <sstream>
#include <string>
#include <unordered_map>

/* DLT LOG */
#define LOG_DEFAULT(level, ...)                                                                    \
    Farm::Logger::getInstance().log_dlt(Farm::Logger::ModuleName::LOG_SRC_DEFAULT, level,          \
                                        __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)

#define LOG_ANIMAL(level, ...)                                                                     \
    Farm::Logger::getInstance().log_dlt(Farm::Logger::ModuleName::ANIMAL, level, __FILE__,         \
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
class Logger {
public:
    enum LogLevel { VERBOSE, DEBUG, INFO, WARNING, ERROR, FATAL };

    enum ModuleName {
        LOG_SRC_ANIMAL,
        LOG_SRC_USER_INTERFACE,
        LOG_SRC_TIME_MANAGEMENT,
        LOG_SRC_MAC_DONALD,
        LOG_SRC_DEFAULT
    };

    Logger();

    static Logger &getInstance();

    void setLogLevel(LogLevel level);

    template <typename... Args> void log_dlt(ModuleName src, LogLevel level, Args... args) {
        if (level >= logLevel) {
            std::lock_guard<std::mutex> lock(this->mMutex);
            std::cout << log_detailed(src, level, args...).str();
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

        logMessageStream << std::endl;
        return logMessageStream;
    }

    template <typename... Args> std::ostringstream log_simple(Args... args) {

        std::ostringstream logMessageStream;

        appendToStream(logMessageStream, args...);

        logMessageStream << std::endl;
        return logMessageStream;
    }

private:
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
    std::mutex mMutex;
};

} // namespace Farm

#endif // LOGGER_HXX
