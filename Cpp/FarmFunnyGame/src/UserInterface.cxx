#include "UserInterface.h"

#include <iostream>

namespace Farm {

UserInterface::UserInterface(std::mutex *Mutex)
    : pMutex(Mutex), mIsPoisonReceived(false) {
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
        const char *userInput = GET_LINE("Please type your commands: ");
        if (userInput == nullptr) {
            LOG_USER(LogLevel::ERROR, "Failed to get user input");
            continue;
        }

        this->mIss.clear();
        this->mIss.str(userInput);
        std::stringstream ss;

        ss << "User Input is: " << userInput;
        LOG_USER(LogLevel::DEBUG, ss.str().c_str());

        this->mCV.notify_one();
        if ((mIsPoisonReceived = ((*userInput) == 0x04))) {
            LOG_USER(LogLevel::INFO, "Poison signal received");
            break;
        }
    }
    LOG_USER(LogLevel::INFO, "Exit UserInterface::start() thread");
}
} // namespace Farm
