#ifndef __MAC_DONALD_H__
#define __MAC_DONALD_H__

#include <vector>

#include "Chicken.h"
#include "Logger.h"
#include "SharedObjects.h"
#include "TimeManager.h"

namespace Farm {

class MacDonald {
private:
    Farm::Logger *mLogger;
    Farm::TimeManager *mTimeManager;

public:
    std::vector<Animal *> mAnimalList;
    Farm::SharedObjects mShared;

    MacDonald(Farm::Logger *Log);
    void start();
    void incAgeAll();
};
}; // namespace Farm

#endif /* __MAC_DONALD_H__ */
