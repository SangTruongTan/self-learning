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
    static constexpr const char* ANIMAL_NAME = "Animal";
    static constexpr const char* CHICKEN_NAME = "Chicken";
    static constexpr const char* DOG_NAME = "Dog";
    static constexpr const char* PIG_NAME = "Pig";
    static constexpr const char* CAT_NAME = "Cat";

    Farm::TimeManager *mTimeManager;
    Farm::UserInterface *mUserInterface;

    std::mutex mMutexUserInterface;
    std::mutex mMutexAnimals;

    const char* getAnimalName(Animal *ani) const;
    void reportAnimals() const;

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
