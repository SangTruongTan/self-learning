#include "TimeManager.h"

#include <chrono>
#include <sstream>
#include <thread>

Farm::TimeManager::TimeManager(Farm::Logger *Log)
    : mLogger(Log), mRunning(true), mHour(0), mDay(0){};
Farm::TimeManager::~TimeManager() {}

void Farm::TimeManager::start(
    std::vector<std::pair<int, std::function<void(void)>>> &timeLists) {
    while (this->mRunning == true) {

        std::stringstream sstr;
        sstr << "mDay=" << this->mDay << ";mHour=" << this->mHour;
        // this->mLogger->LogI(sstr.str());
        for (auto const &time : timeLists) {
            if (time.first == this->mHour) {
                time.second();
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        if (++mHour == 24) {
            this->mDay += 1;
            this->mHour = 0;
        }
    }
}
