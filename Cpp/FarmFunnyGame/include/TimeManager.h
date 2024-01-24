#ifndef __TIME_MANAGER_H__
#define __TIME_MANAGER_H__

#include <atomic>
#include <functional>
#include <vector>

#include "Logger.h"

namespace Farm {
class TimeManager {
private:
    bool mRunning;
    int mHour;
    int mDay;

public:
    std::atomic<bool> mIsPoisonReceived;

    /**
     * @brief Construct a new Time Manager object
     */
    TimeManager();

    /**
     * @brief Destroy the Time Manager object
     *
     */
    ~TimeManager();

    void
    start(std::vector<std::pair<int, std::function<void(void)>>> &timeLists);

};
};     // namespace Farm
#endif /* __TIME_MANAGER_H__ */
