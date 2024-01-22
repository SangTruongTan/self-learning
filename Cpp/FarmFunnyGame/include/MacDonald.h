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
    Farm::TimeManager *mTimeManager;
    Farm::UserInterface *mUserInterface;

    std::mutex mMutexUserInterface;
    std::mutex mMutexAnimals;
public:
    std::vector<Animal *> mAnimalList;
    Farm::SharedObjects mShared;

    MacDonald();
    void start();
    void handleCommands();

    void incAgeAll();
    bool isAnimalExist(const char *name);
};
}; // namespace Farm

#endif /* __MAC_DONALD_H__ */
