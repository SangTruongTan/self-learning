#include "TimeManager.h"

#include <chrono>
#include <sstream>
#include <thread>

namespace Farm {
TimeManager::TimeManager()
    : mRunning(true), mHour(0), mDay(0), mIsPoisonReceived(false){};
TimeManager::~TimeManager() {}

void TimeManager::start(
    std::vector<std::pair<const int, std::function<void(void)>>> &timeLists) {
    while (this->mRunning == true) {

        if (mIsPoisonReceived == true) {
            LOG_CLOCK(LogLevel::INFO, "The poison signal received");
            break;
        }
        std::stringstream sstr;
        sstr << "mDay=" << this->mDay << "; mHour=" << this->mHour << ":00  ";
        LOG_CLOCK_SCREEN(sstr.str().c_str());

        for (auto const &time : timeLists) {
            if (time.first == this->mHour) {
                time.second();
            } else if (time.first == TimeManager::CONTINUOUS) {
                time.second();
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        if (++mHour == 24) {
            this->mDay += 1;
            this->mHour = 0;
        }
    }
    LOG_CLOCK(LogLevel::INFO, "Exit TimeManager::start() thread");
}
} // namespace Farm
