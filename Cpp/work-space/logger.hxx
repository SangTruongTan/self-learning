#ifndef LOGGER_HXX
#define LOGGER_HXX

#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>


#define LOGGER_DLT(logger, level, ...) logger->log_dlt(level, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)

namespace Farm {
    class Logger {
    public:
        enum LogLevel {
            VERBOSE,
            DEBUG,
            INFO,
            WARNING,
            ERROR,
            FATAL
        };

    Logger();

    void setLogLevel(LogLevel level);

    template<typename... Args>
    void log_dlt(LogLevel level, Args... args) {
        if (level >= logLevel) {
            std::cout << log(level, args...).str();
        }
    }

    template<typename... Args>
    std::ostringstream log(LogLevel level, const char* file, const char* func, int line, Args... args) {


        std::ostringstream logMessageStream;
        logMessageStream << file << ":" << line << " ";
        logMessageStream << func << "() ";

        std::string levelStr = logLevelStrings.at(level);
        logMessageStream << "[" << levelStr << "] ";

        appendToStream(logMessageStream, args...);

        logMessageStream << std::endl;
        return logMessageStream;
    }

    private:
        LogLevel logLevel = INFO;

        Logger(const Logger& rhs);
        Logger& operator=(const Logger& rhs);

        template<typename T, typename... Args>
        void appendToStream(std::ostringstream& stream, T value, Args... args) {
            stream << value;  // Append the current argument to the stream
            appendToStream(stream, args...);  // Recursively append remaining arguments
        }

        void appendToStream(std::ostringstream& /*stream*/) {
            // Base case for the variadic template recursion
        }

        static const std::unordered_map<LogLevel, std::string> logLevelStrings;
    };

}  // namespace Farm

#endif  // LOGGER_HXX
