#include "Chicken.h"

namespace Farm {

Chicken::Chicken(std::string Name, SharedObjects &shared)
    : Animal(Name, shared) {
    std::stringstream ss;
    ss << "A new Chicken named: \"" << this->mName << "\" has been born";
    LOG_ANIMAL(LogLevel::INFO, ss.str());
    mType = AnimalType::CHICKEN;
}

Chicken::~Chicken() {
    std::stringstream ss;
    ss << "Chicken [" << this->mName << "] instance is destroying!";
    LOG_ANIMAL(LogLevel::INFO, ss.str());
}

void Chicken::sound(int NumOfSound) {
    for (int i = 0; i < NumOfSound; i++) {
        LOG_ANIMAL(LogLevel::INFO, std::string(CHICKENS_SOUND));
        LOG_CONSOLE(LogLevel::INFO, "[", mName, "] => ", CHICKENS_SOUND, "\n");
    }
    if (mShared.soundCallback) {
        LOG_ANIMAL(LogLevel::DEBUG, "Invoke sound callback function");
        mShared.soundCallback(mType, NumOfSound);
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

bool Chicken::isSalable(void) const { return (mWeight == CHICKEN_MAX_WEIGHT); }

void Chicken::killAnimal(void) {
    std::stringstream ss;
    ss << "Animal [" << mName << "] is going to be dead\n";
    LOG_ANIMAL(LogLevel::INFO, ss.str());
    LOG_CONSOLE(LogLevel::INFO, ss.str());
    this->sound(Animal::CHICKEN_NUM_SOUND_WHEN_DIE);
}

int Chicken::getSellPrice(void) const { return CHICKEN_SELL_PRICE; }

AnimalType Chicken::getType(void) const { return mType; }

int Chicken::checkHappyReductionBySounds(void) {
    int offset = (numOfSounds.at(AnimalType::CAT) +
                  numOfSounds.at(AnimalType::DOG) +
                  numOfSounds.at(AnimalType::PIG)) %
                 CHICKEN_REDUCTION_CONDITION_BY_SOUND;
    LOG_ANIMAL(LogLevel::INFO, "Happy Index new = ", mHappyIndex, " - ", offset);
    mHappyIndex -= offset;
    return mHappyIndex;
}

Animal::AnimalError Chicken::isEdible(void) {
    return AnimalError::AnimalNoError;
}

} // namespace Farm
