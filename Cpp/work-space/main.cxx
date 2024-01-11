#include "logger.hxx"

int main() {
    Farm::Logger* logger = new Farm::Logger();
    logger->setLogLevel(Farm::Logger::LogLevel::DEBUG);
    LOGGER_DLT(logger, Farm::Logger::LogLevel::DEBUG, "abcd ", 55);
    return 0;
}