#include "Logger.h"

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
    iBuffer = new char[1024];
}

void Logger::deinitScreen() {
    LOG_DEFAULT(LogLevel::INFO, "Deinitializing the Screen");
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
