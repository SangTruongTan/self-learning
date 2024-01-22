#include "UserInterface.h"

#include <iostream>

namespace Farm {

UserInterface::UserInterface(std::mutex *Mutex) : pMutex(Mutex) {
    LOG_USER(LogLevel::INFO, "Initiated User Interface class");
}

UserInterface::~UserInterface() {
    LOG_USER(LogLevel::INFO, "De-initiated User Interface class");
}

void UserInterface::start() {
    LOG_USER(LogLevel::INFO, "Enter UserInterface::start()");
    while (true) {
        std::unique_lock<std::mutex> lock(*this->pMutex);
        this->mCV.wait(lock, [this] { return this->mIss.peek() == EOF; });
        this->mUserInput.clear();
        this->mIss.clear();
        LOG_CONSOLE(LogLevel::INFO, "Please type your commands: ");
        std::getline(std::cin, this->mUserInput);

        this->mIss.str(this->mUserInput);
        std::stringstream ss;
        ss << "User Input is: " << this->mUserInput.c_str();
        LOG_USER(LogLevel::DEBUG, ss.str().c_str());

        this->mCV.notify_one();
    }
    LOG_USER(LogLevel::INFO, "Exit UserInterface::start()");
}
} // namespace Farm
