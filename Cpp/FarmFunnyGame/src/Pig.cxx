/**
 ******************************************************************************
 * @file           : Pig.cxx
 * @brief          : Pig's source file.
 ******************************************************************************
 * @attention
 *
 * BSD 3-Clause License
 *
 * Copyright (c) 2024, Sang Tan Truong.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of Sang Tan Truong nor the names of its contributors may
 *    be used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "Pig.h"

#include <random>

/* Definitions ---------------------------------------------------------------*/
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
