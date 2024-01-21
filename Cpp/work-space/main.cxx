#include "logger.hxx"

int main() {
    Farm::Logger& loggerIns = Farm::Logger::getInstance();
    loggerIns.setLogLevel(Farm::Logger::LogLevel::VERBOSE);
    LOG_CLOCK(Farm::Logger::LogLevel::INFO, "abcd ", 55);
    LOG_CONSOLE(Farm::Logger::DEBUG, "2Hello", 5.5);
    return 0;
}