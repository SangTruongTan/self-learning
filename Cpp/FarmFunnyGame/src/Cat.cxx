#include "Cat.h"

namespace Farm {

Cat::Cat(std::string Name, SharedObjects &shared) : Animal(Name, shared) {
    std::stringstream ss{};
    ss << "A new Cat named: \"" << this->mName << "\" has been born";
    LOG_ANIMAL(LogLevel::INFO, ss.str());
    mType = AnimalType::CAT;
}

Cat::~Cat() {
    std::stringstream ss{};
    ss << "Cat [" << this->mName << "] instance is destroying!";
    LOG_ANIMAL(LogLevel::INFO, ss.str());
}

void Cat::sound(int NumOfSound) {
    for (int i = 0; i < NumOfSound; i++) {
        LOG_ANIMAL(LogLevel::INFO, std::string(CAT_SOUND));
        LOG_CONSOLE(LogLevel::INFO, "[", mName, "] => ", CAT_SOUND, "\n");
    }
    if (mShared.soundCallback) {
        LOG_ANIMAL(LogLevel::DEBUG, "Invoke sound callback function");
        mShared.soundCallback(mType, NumOfSound);
    }
}

bool Cat::exceedLifeTime(void) {
    bool retVal = false;
    if (this->getAge() >= Animal::CAT_LIFE_TIME) {
        retVal = true;
    }
    return retVal;
}

/**
 * This API will be invoked at 12:00AM-
 */
void Cat::scanAnimal(void) {
    LOG_ANIMAL(LogLevel::DEBUG, "[", mName, "] scanAnimal()");
    /* Check weight. */
    if (mFedToday == true) {
        if (mFeedConsecutiveDays >= CAT_WEIGHT_CONSECUTIVE_DAYS) {
            mWeight += CAT_GAIN_WEIGHT;
            if (mWeight >= CAT_MAX_WEIGHT) {
                mWeight = CAT_MAX_WEIGHT;
            }
        }
    } else {
        mFeedConsecutiveDays = 0;
        LOG_ANIMAL(LogLevel::DEBUG, "[", mName, "] Reset mFeedConsecutiveDays");
    }
    mFedToday = false;
    LOG_ANIMAL(LogLevel::DEBUG, "[", mName, "] Weight => ", mWeight);

    /* Check go out status. */
    if (mIsWentOutToday == true || mIsOutdoor == true) {
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

bool Cat::isSalable(void) const { return (mAge > CAT_AGE_TO_SELL); }

void Cat::killAnimal(void) {
    std::stringstream ss{};
    ss << "Animal [" << mName << "] is going to be dead\n";
    LOG_ANIMAL(LogLevel::INFO, ss.str());
    LOG_CONSOLE(LogLevel::INFO, ss.str());
    this->sound(Animal::CAT_NUM_SOUND_WHEN_DIE);
}

int Cat::getSellPrice(void) const { return CAT_SELL_PRICE; }

AnimalType Cat::getType(void) const { return mType; }

int Cat::checkHappyReductionBySounds(void) {
    int offset = (numOfSounds.at(AnimalType::CHICKEN) +
                  numOfSounds.at(AnimalType::DOG)) %
                 CAT_REDUCTION_CONDITION_BY_SOUND;
    LOG_ANIMAL(LogLevel::INFO, "Happy Index new = ", mHappyIndex, " - ",
               offset);
    gainHappyIndex(-1 * offset);
    return mHappyIndex;
}

Animal::AnimalError Cat::isEdible(void) {
    AnimalError retval{AnimalNoError};
    if (mFedToday == true) {
        retval = AnimalError::AnimalAlreadyFed;
    } else if (mHappyIndex < Animal::HAPPY_INDEX_CONDITION_TO_EAT) {
        retval = AnimalError::AnimalHappyIndexAlert;
    } else if (mAge < CAT_AGE_TO_EAT) {
        retval = AnimalError::AnimalAgeNotAdequate;
    }

    return retval;
}

bool Cat::isReproducible(void) {
    return (mAge == CAT_AGE_TO_REPRODUCE) &&
           (mWeight >= CAT_WEIGHT_TO_REPRODUCE) &&
           (mHappyIndex >= CAT_HAPPY_INDEX_TO_REPRODUCE);
}

Animal *Cat::reproduce(std::string name) const {
    return new Cat(name, mShared);
}

int Cat::getNumberOfChilds(void) { return CAT_NUM_REPRODUCE; }

void Cat::soundWhenBorn(void) { sound(CAT_NUM_SOUND_WHEN_BORN); }

int Cat::gainIntelligentIndex([[maybe_unused]] int offset) {
    return INTELLIGENT_INDEX_NOT_APPLICABLE;
}

int Cat::getIntelligentIndex(void) const {
    return INTELLIGENT_INDEX_NOT_APPLICABLE;
}

Animal::AnimalError Cat::trainAnimal(void) {
    LOG_FARM(LogLevel::ERROR,
             "This service isn't supported for the functionality");
    return Animal::AnimalError::AnimalNotSupportedTraining;
}

} // namespace Farm
