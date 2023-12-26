#include "UserInterface.h"

#include <iostream>

Farm::UserInterface::UserInterface(Farm::Logger *Log, std::istringstream *Iss,
                                   std::mutex *Mutex,
                                   std::condition_variable *CV) {
    this->mLogger = Log;
    this->pIss = Iss;
    this->pMutex = Mutex;
    this->pCV = CV;
    this->mLogger->LogI("Initiated User Interface class");
}

Farm::UserInterface::~UserInterface() {
    this->mLogger->LogI("De-initiated User Interface class");
}

void Farm::UserInterface::start() {
    this->mLogger->LogI("Enter Farm::UserInterface::start()");
    while (true) {
        std::unique_lock<std::mutex> lock(*this->pMutex);
        this->pCV->wait(lock, [this] { return this->pIss->peek() == EOF; });
        this->mUserInput.clear();
        this->pIss->clear();
        std::cout << "Please type your commands: ";
        std::getline(std::cin, this->mUserInput);

        this->pIss->str(this->mUserInput);
        std::stringstream ss;
        ss << "User Input is: " << this->mUserInput.c_str();
        this->mLogger->LogD(ss.str().c_str());

        this->pCV->notify_one();
    }
    this->mLogger->LogI("Exit Farm::UserInterface::start()");
}
