#ifndef __MAC_DONALD_H__
#define __MAC_DONALD_H__

#include <condition_variable>
#include <mutex>
#include <sstream>
#include <vector>

#include "Chicken.h"
#include "Logger.h"
#include "SharedObjects.h"
#include "UserInterface.h"
#include "TimeManager.h"

namespace Farm {

class MacDonald {
private:
    Farm::Logger *mLogger;
    Farm::TimeManager *mTimeManager;
    Farm::UserInterface *mUserInterface;

    std::mutex mMutex;
    std::condition_variable mCV;
    std::istringstream mIss;

public:
    std::vector<Animal *> mAnimalList;
    Farm::SharedObjects mShared;

    MacDonald(Farm::Logger *Log);
    void start();
    void handleCommands();

    void incAgeAll();
};
}; // namespace Farm

#endif /* __MAC_DONALD_H__ */