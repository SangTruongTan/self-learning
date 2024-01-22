#include "Logger.h"

namespace Farm {

Logger::Logger(void) {}

Logger::~Logger(void) {
    LOG_DEFAULT(Farm::LogLevel::INFO, "Deinitialize Logger module");
    DLT_UNREGISTER_CONTEXT(ctx);
    DLT_UNREGISTER_APP();
}

Logger &Logger::getInstance() {
    static Logger instance{Logger()};
    return instance;
}

void Logger::setLogLevel(LogLevel level) { logLevel = level; }

void Logger::setAppContext(std::string AppId, std::string ContextId) {
    Logger& ins = Logger::getInstance();

    DLT_REGISTER_APP(AppId.c_str(), "New Application");
    DLT_REGISTER_CONTEXT(ins.ctx, ContextId.c_str(), "Test Context for Logging");
    LOG_DEFAULT(Farm::LogLevel::INFO, "Initialized Logger module");
}

const std::unordered_map<LogLevel, std::string> Logger::logLevelStrings = {
    {Farm::LogLevel::VERBOSE, "VERBOSE"}, {Farm::LogLevel::DEBUG, "DEBUG"},
    {Farm::LogLevel::INFO, "INFO"},       {Farm::LogLevel::WARNING, "WARNING"},
    {Farm::LogLevel::ERROR, "ERROR"},     {Farm::LogLevel::FATAL, "FATAL"}};

const std::unordered_map<Logger::ModuleName, std::string> Logger::moduleNameStrings = {
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

