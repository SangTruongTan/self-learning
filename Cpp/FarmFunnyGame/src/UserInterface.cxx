#include "UserInterface.h"

#include <iostream>

Farm::UserInterface::UserInterface(Farm::Logger *Log, std::mutex *Mutex) :
    mLogger(Log), pMutex(Mutex) {
    this->mLogger->LogI("Initiated User Interface class");
}

Farm::UserInterface::~UserInterface() {
    this->mLogger->LogI("De-initiated User Interface class");
}

void Farm::UserInterface::start() {
    this->mLogger->LogI("Enter Farm::UserInterface::start()");
    while (true) {
        std::unique_lock<std::mutex> lock(*this->pMutex);
        this->mCV.wait(lock, [this] { return this->mIss.peek() == EOF; });
        this->mUserInput.clear();
        this->mIss.clear();
        std::cout << "Please type your commands: ";
        std::getline(std::cin, this->mUserInput);

        this->mIss.str(this->mUserInput);
        std::stringstream ss;
        ss << "User Input is: " << this->mUserInput.c_str();
        this->mLogger->LogD(ss.str().c_str());

        this->mCV.notify_one();
    }
    this->mLogger->LogI("Exit Farm::UserInterface::start()");
}
