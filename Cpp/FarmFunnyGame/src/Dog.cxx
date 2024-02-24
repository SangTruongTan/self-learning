#include "Dog.h"

namespace Farm {

Dog::Dog(std::string Name, SharedObjects &shared) : Animal(Name, shared) {
    std::stringstream ss{};
    ss << "A new Dog named: \"" << this->mName << "\" has been born";
    LOG_ANIMAL(LogLevel::INFO, ss.str());
    mType = AnimalType::DOG;
}

Dog::~Dog() {
    std::stringstream ss{};
    ss << "Dog [" << this->mName << "] instance is destroying!";
    LOG_ANIMAL(LogLevel::INFO, ss.str());
}

void Dog::sound(int NumOfSound) {
    for (int i = 0; i < NumOfSound; i++) {
        LOG_ANIMAL(LogLevel::INFO, std::string(DOG_SOUND));
        LOG_CONSOLE(LogLevel::INFO, "[", mName, "] => ", DOG_SOUND, "\n");
    }
    if (mShared.soundCallback) {
        LOG_ANIMAL(LogLevel::DEBUG, "Invoke sound callback function");
        mShared.soundCallback(mType, NumOfSound);
    }
}

bool Dog::exceedLifeTime(void) {
    bool retVal = false;
    if (this->getAge() >= Animal::DOG_LIFE_TIME) {
        retVal = true;
    }
    return retVal;
}

/**
 * This API will be invoked at 12:00AM-
 */
void Dog::scanAnimal(void) {
    LOG_ANIMAL(LogLevel::DEBUG, "[", mName, "] scanAnimal()");
    /* Check weight. */
    if (mFedToday == true) {
        if (mFeedConsecutiveDays >= DOG_WEIGHT_CONSECUTIVE_DAYS) {
            mWeight += DOG_GAIN_WEIGHT;
            if (mWeight >= DOG_MAX_WEIGHT) {
                mWeight = DOG_MAX_WEIGHT;
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

    /* Intelligent Index reset flag. */
    isTrainedToday = false;
}

bool Dog::isSalable(void) const { return (mAge > 12); }

void Dog::killAnimal(void) {
    std::stringstream ss{};
    ss << "Animal [" << mName << "] is going to be dead\n";
    LOG_ANIMAL(LogLevel::INFO, ss.str());
    LOG_CONSOLE(LogLevel::INFO, ss.str());
    this->sound(Animal::DOG_NUM_SOUND_WHEN_DIE);
}

int Dog::getSellPrice(void) const {
    int retval{DOG_SELL_PRICE};
    if (mIntelligentIndex >= INTELLIGENT_INDEX_GAIN_SELL_PRICE) {
        retval = DOG_INTELLIGENT_SELL_PRICE;
    }
    return retval;
}

AnimalType Dog::getType(void) const { return mType; }

int Dog::checkHappyReductionBySounds(void) {
    int offset =
        (numOfSounds.at(AnimalType::CAT)) % DOG_REDUCTION_CONDITION_BY_SOUND;
    LOG_ANIMAL(LogLevel::INFO, "Happy Index new = ", mHappyIndex, " - ",
               offset);
    gainHappyIndex(-1 * offset);
    return mHappyIndex;
}

Animal::AnimalError Dog::isEdible(void) {
    AnimalError retval{AnimalNoError};
    if (mFedToday == true) {
        retval = AnimalError::AnimalAlreadyFed;
    } else if (mHappyIndex < Animal::HAPPY_INDEX_CONDITION_TO_EAT) {
        retval = AnimalError::AnimalHappyIndexAlert;
    } else if (mAge < DOG_AGE_TO_EAT) {
        retval = AnimalError::AnimalAgeNotAdequate;
    }

    return retval;
}

bool Dog::isReproducible(void) {
    return (mAge == DOG_AGE_TO_REPRODUCE) &&
           (mWeight >= DOG_WEIGHT_TO_REPRODUCE) &&
           (mHappyIndex >= DOG_HAPPY_INDEX_TO_REPRODUCE) &&
           (mIntelligentIndex >= INTELLIGENT_INDEX_REPRODUCIBLE);
}

Animal *Dog::reproduce(std::string name) const {
    return new Dog(name, mShared);
}

int Dog::getNumberOfChilds(void) { return DOG_NUM_REPRODUCE; }

void Dog::soundWhenBorn(void) { sound(DOG_NUM_SOUND_WHEN_BORN); }

int Dog::gainIntelligentIndex(int offset) {
    LOG_ANIMAL(LogLevel::INFO, "[", mName, "] Intelligent index changed from ",
               mIntelligentIndex, " => ", mIntelligentIndex + offset);
    mIntelligentIndex += offset;
    if (mIntelligentIndex > INTELLIGENT_INDEX_MAX) {
        mIntelligentIndex = INTELLIGENT_INDEX_MAX;
    } else if (mIntelligentIndex < INTELLIGENT_INDEX_MIN) {
        mIntelligentIndex = INTELLIGENT_INDEX_MIN;
    }
    return mIntelligentIndex;
}

int Dog::getIntelligentIndex(void) const {
    return mIntelligentIndex;
}

Animal::AnimalError Dog::trainAnimal(void) {
    Animal::AnimalError retval{AnimalNoError};
    if (isTrainedToday == true) {
        retval = Animal::AnimalError::AnimalAlreadyTrainedToday;
        LOG_ANIMAL(LogLevel::INFO,
                   "[", mName, "] has already been trained today");
    } else {
        isTrainedToday = true;
        gainIntelligentIndex(Animal::INTELLIGENT_GAIN_FACTOR);
        LOG_ANIMAL(LogLevel::INFO, "[", mName, "] is beeing trained");
    }
    return retval;
}

} // namespace Farm
