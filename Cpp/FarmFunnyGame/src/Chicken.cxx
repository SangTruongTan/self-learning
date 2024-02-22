#include "Chicken.h"

#include <random>

namespace Farm {

Chicken::Chicken(std::string Name, SharedObjects &shared)
    : Animal(Name, shared) {
    std::stringstream ss{};
    ss << "A new Chicken named: \"" << this->mName << "\" has been born";
    LOG_ANIMAL(LogLevel::INFO, ss.str());
    mType = AnimalType::CHICKEN;
}

Chicken::~Chicken() {
    std::stringstream ss{};
    ss << "Chicken [" << this->mName << "] instance is destroying!";
    LOG_ANIMAL(LogLevel::INFO, ss.str());
}

void Chicken::sound(int NumOfSound) {
    for (int i = 0; i < NumOfSound; i++) {
        LOG_ANIMAL(LogLevel::INFO, std::string(CHICKEN_SOUND));
        LOG_CONSOLE(LogLevel::INFO, "[", mName, "] => ", CHICKEN_SOUND, "\n");
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

    /* Check go out status. */
    if (mIsOutdoor == true) {
        /* Remark: except Cats. */
        letAnimalGoBack();
    }
    if (mIsWentOutToday == true) {
        mNotGoOutdoorConsecutiveDays = 0;
        mIsWentOutToday = false;
    } else {
        mNotGoOutdoorConsecutiveDays += 1;
    }

    if (mNotGoOutdoorConsecutiveDays >= Animal::NOT_GO_OUT_CONSECUTIVE) {
        gainHappyIndex(Animal::GAIN_ON_CONSECUTIVE_INDOOR);
    }

    if (mHappyIndex == 0) {
        mZeroHappyIndexConsecutiveDays += 1;
    } else {
        mZeroHappyIndexConsecutiveDays = 0;
    }
}

bool Chicken::isSalable(void) const { return (mWeight == CHICKEN_MAX_WEIGHT); }

void Chicken::killAnimal(void) {
    std::stringstream ss{};
    ss << "Animal [" << mName << "] is going to be dead\n";
    LOG_ANIMAL(LogLevel::INFO, ss.str());
    LOG_CONSOLE(LogLevel::INFO, ss.str());
    this->sound(Animal::CHICKEN_NUM_SOUND_WHEN_DIE);
}

int Chicken::getSellPrice(void) const { return CHICKEN_SELL_PRICE; }

AnimalType Chicken::getType(void) const { return mType; }

int Chicken::checkHappyReductionBySounds(void) {
    int offset =
        (numOfSounds.at(AnimalType::CAT) + numOfSounds.at(AnimalType::DOG) +
         numOfSounds.at(AnimalType::PIG)) %
        CHICKEN_REDUCTION_CONDITION_BY_SOUND;
    LOG_ANIMAL(LogLevel::INFO, "Happy Index new = ", mHappyIndex, " - ",
               offset);
    gainHappyIndex(-1 * offset);
    return mHappyIndex;
}

Animal::AnimalError Chicken::isEdible(void) {
    AnimalError retval{AnimalNoError};
    if (mFedToday == true) {
        retval = AnimalError::AnimalAlreadyFed;
    } else if (mHappyIndex < Animal::HAPPY_INDEX_CONDITION_TO_EAT) {
        retval = AnimalError::AnimalHappyIndexAlert;
    } else if (mAge < CHICKEN_AGE_TO_EAT) {
        retval = AnimalError::AnimalAgeNotAdequate;
    }

    return retval;
}

bool Chicken::isReproducible(void) {
    return (mAge == CHICKEN_AGE_TO_REPRODUCE) &&
           (mWeight >= CHICKEN_WEIGHT_TO_REPRODUCE) &&
           (mHappyIndex >= CHICKEN_HAPPY_INDEX_TO_REPRODUCE);
}

Animal *Chicken::reproduce(std::string name) const {
    return new Chicken(name, mShared);
}

int Chicken::getNumberOfChilds(void) {
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<int> distribution(
        CHICKEN_NUM_REPRODUCE_RANDOM_MIN, CHICKEN_NUM_REPRODUCE_RANDOM_MAX);
    return distribution(generator);
}

void Chicken::soundWhenBorn(void) { sound(CHICKEN_NUM_SOUND_WHEN_BORN); }

int Chicken::gainIntelligentIndex([[maybe_unused]] int offset) {
    return INTELLIGENT_INDEX_NOT_APPLICABLE;
}

int Chicken::getIntelligentIndex(void) const {
    return INTELLIGENT_INDEX_NOT_APPLICABLE;
}

} // namespace Farm
