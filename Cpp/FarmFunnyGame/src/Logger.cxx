#include <string>

#include "Logger.h"
#include <iostream>

Farm::Logger::Logger(std::string AppId, std::string ContextId) {
    DLT_REGISTER_APP(AppId.c_str(), "New Application");
    DLT_REGISTER_CONTEXT(this->ctx, ContextId.c_str(), "Test Context for Logging");
}

Farm::Logger::~Logger(void) {
    this->LogI("Deinitialize Logger module");
    DLT_UNREGISTER_CONTEXT(ctx);
    DLT_UNREGISTER_APP();
}

void Farm::Logger::LogE(std::string Message) {
    DLT_LOG(this->ctx, DLT_LOG_ERROR, DLT_CSTRING(Message.c_str()));
}

void Farm::Logger::LogI(std::string Message) {
    DLT_LOG(this->ctx, DLT_LOG_INFO, DLT_CSTRING(Message.c_str()));
}

void Farm::Logger::LogD(std::string Message) {
    DLT_LOG(this->ctx, DLT_LOG_DEBUG, DLT_CSTRING(Message.c_str()));
}

void Farm::Logger::LogV(std::string Message) {
    DLT_LOG(this->ctx, DLT_LOG_VERBOSE, DLT_CSTRING(Message.c_str()));
}
