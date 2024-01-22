#include "logger.hxx"

namespace Farm {
Logger::Logger() {}

Logger &Logger::getInstance() {
    static Logger instance{Logger()};
    return instance;
}

void Logger::setLogLevel(LogLevel level) { logLevel = level; }

const std::unordered_map<Logger::LogLevel, std::string> Logger::logLevelStrings = {
    {Logger::LogLevel::VERBOSE, "VERBOSE"}, {Logger::LogLevel::DEBUG, "DEBUG"},
    {Logger::LogLevel::INFO, "INFO"},       {Logger::LogLevel::WARNING, "WARNING"},
    {Logger::LogLevel::ERROR, "ERROR"},     {Logger::LogLevel::FATAL, "FATAL"}};

const std::unordered_map<Logger::ModuleName, std::string> Logger::moduleNameStrings = {
    {Logger::ModuleName::LOG_SRC_ANIMAL, "ANIMAL"},
    {Logger::ModuleName::LOG_SRC_USER_INTERFACE, "USER"},
    {Logger::ModuleName::LOG_SRC_TIME_MANAGEMENT, "CLOCK"},
    {Logger::ModuleName::LOG_SRC_MAC_DONALD, "FARM"},
    {Logger::ModuleName::LOG_SRC_DEFAULT, "DEFAULT"}};

} // namespace Farm
