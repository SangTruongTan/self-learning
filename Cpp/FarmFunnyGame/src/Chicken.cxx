#include "Chicken.h"

namespace Farm {

Chicken::Chicken(std::string Name, SharedObjects &shared)
    : Animal(Name, shared) {
    std::stringstream ss;
    ss << "A new Chicken named: \"" << this->mName << "\" has been born";
    LOG_ANIMAL(LogLevel::INFO, ss.str());
}

Chicken::~Chicken() {
    this->sound(Animal::CHICKEN_NUM_SOUND_WHEN_DIE);
    std::stringstream ss;
    ss << "Chicken [" << this->mName << "] has been died!";
    LOG_ANIMAL(LogLevel::INFO, ss.str());
    LOG_CONSOLE(LogLevel::INFO, ss.str().c_str(), "\n");
}

void Chicken::sound(int NumOfSound) {
    for (int i = 0; i < NumOfSound; i++) {
        this->mShared.ChickenSound++;
        LOG_ANIMAL(LogLevel::INFO, std::string(CHICKENS_SOUND));
        LOG_CONSOLE(LogLevel::INFO, "[", mName, "] => ", CHICKENS_SOUND, "\n");
    }
}

bool Chicken::exceedLifeTime(void) {
    bool retVal = false;
    if (this->getAge() >= Animal::CHICKEN_LIFE_TIME) {
        retVal = true;
    }
    return retVal;
}

/**
 * This API will be invoked at 12:00AM-
*/
void Chicken::scanAnimal(void) {
    LOG_ANIMAL(LogLevel::DEBUG, "[", mName, "] scanAnimal()");
    /* Check weight. */
    if (mFedToday == true) {
        if (mFeedConsecutiveDays >= CHICKEN_WEIGHT_CONSECUTIVE_DAYS) {
            mWeight += CHICKEN_GAIN_WEIGHT;
            if (mWeight >= CHICKEN_MAX_WEIGHT) {
                mWeight = CHICKEN_MAX_WEIGHT;
            }
        }
    } else {
        mFeedConsecutiveDays = 0;
        LOG_ANIMAL(LogLevel::DEBUG, "[", mName, "] Reset mFeedConsecutiveDays");
    }
    mFedToday = false;
    LOG_ANIMAL(LogLevel::DEBUG, "[", mName, "] Weight => ", mWeight);
}

} // namespace Farm
