#include "logger.hxx"

namespace Farm {
    Logger::Logger() {}

    void Logger::setLogLevel(LogLevel level) {
        logLevel = level;
    }

    const std::unordered_map<Logger::LogLevel, std::string> Logger::logLevelStrings = {
        { Logger::LogLevel::VERBOSE, "VERBOSE" },
        { Logger::LogLevel::DEBUG, "DEBUG" },
        { Logger::LogLevel::INFO, "INFO" },
        { Logger::LogLevel::WARNING, "WARNING" },
        { Logger::LogLevel::ERROR, "ERROR" },
        { Logger::LogLevel::FATAL, "FATAL" }
    };
}  // namespace Farm
