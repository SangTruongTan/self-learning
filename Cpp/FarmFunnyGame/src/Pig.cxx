#include "Pig.h"

#include <random>

namespace Farm {

Pig::Pig(std::string Name, SharedObjects &shared) : Animal(Name, shared) {
    std::stringstream ss{};
    ss << "A new Pig named: \"" << this->mName << "\" has been born";
    LOG_ANIMAL(LogLevel::INFO, ss.str());
    mType = AnimalType::PIG;
}

Pig::~Pig() {
    std::stringstream ss{};
    ss << "Pig [" << this->mName << "] instance is destroying!";
    LOG_ANIMAL(LogLevel::INFO, ss.str());
}

void Pig::sound(int NumOfSound) {
    for (int i = 0; i < NumOfSound; i++) {
        LOG_ANIMAL(LogLevel::INFO, std::string(PIG_SOUND));
        LOG_CONSOLE(LogLevel::INFO, "[", mName, "] => ", PIG_SOUND, "\n");
    }
    if (mShared.soundCallback) {
        LOG_ANIMAL(LogLevel::DEBUG, "Invoke sound callback function");
        mShared.soundCallback(mType, NumOfSound);
    }
}

bool Pig::exceedLifeTime(void) {
    bool retVal = false;
    if (this->getAge() >= Animal::PIG_LIFE_TIME) {
        retVal = true;
    }
    return retVal;
}

/**
 * This API will be invoked at 12:00AM-
 */
void Pig::scanAnimal(void) {
    LOG_ANIMAL(LogLevel::DEBUG, "[", mName, "] scanAnimal()");
    /* Check weight. */
    if (mFedToday == true) {
        if (mFeedConsecutiveDays >= PIG_WEIGHT_CONSECUTIVE_DAYS) {
            mWeight += PIG_GAIN_WEIGHT;
            if (mWeight >= PIG_MAX_WEIGHT) {
                mWeight = PIG_MAX_WEIGHT;
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
}

bool Pig::isSalable(void) const { return (mAge > PIG_AGE_TO_SELL); }

void Pig::killAnimal(void) {
    std::stringstream ss{};
    ss << "Animal [" << mName << "] is going to be dead\n";
    LOG_ANIMAL(LogLevel::INFO, ss.str());
    LOG_CONSOLE(LogLevel::INFO, ss.str());
    this->sound(Animal::PIG_NUM_SOUND_WHEN_DIE);
}

int Pig::getSellPrice(void) const { return PIG_SELL_PRICE * mWeight; }

AnimalType Pig::getType(void) const { return mType; }

int Pig::checkHappyReductionBySounds(void) {
    return HAPPY_INDEX_NOT_APPLICABLE;
}

Animal::AnimalError Pig::isEdible(void) {
    AnimalError retval{AnimalNoError};
    if (mFedToday == true) {
        retval = AnimalError::AnimalAlreadyFed;
    } else if (mAge < PIG_AGE_TO_EAT) {
        retval = AnimalError::AnimalAgeNotAdequate;
    }

    return retval;
}

bool Pig::isReproducible(void) {
    return (mAge == PIG_AGE_TO_REPRODUCE) &&
           (mWeight >= PIG_WEIGHT_TO_REPRODUCE);
}

Animal *Pig::reproduce(std::string name) const {
    return new Pig(name, mShared);
}

int Pig::getNumberOfChilds(void) {
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<int> distribution(
        PIG_NUM_REPRODUCE_RANDOM_MIN, PIG_NUM_REPRODUCE_RANDOM_MAX);
    return distribution(generator);
}

void Pig::soundWhenBorn(void) { sound(PIG_NUM_SOUND_WHEN_BORN); }

int Pig::gainIntelligentIndex([[maybe_unused]] int offset) {
    return INTELLIGENT_INDEX_NOT_APPLICABLE;
}

int Pig::getIntelligentIndex(void) const {
    return INTELLIGENT_INDEX_NOT_APPLICABLE;
}

Animal::AnimalError Pig::trainAnimal(void) {
    LOG_FARM(LogLevel::ERROR,
             "This service isn't supported for the functionality");
    return Animal::AnimalError::AnimalNotSupportedTraining;
}

} // namespace Farm
