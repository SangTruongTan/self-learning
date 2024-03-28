/**
 ******************************************************************************
 * @file           : Animal.h
 * @brief          : Animal's header file.
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ANIMAL_H__
#define __ANIMAL_H__

/* Includes ------------------------------------------------------------------*/
#include <cstdint>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "Logger.h"
#include "SharedObjects.h"

/* Declarations --------------------------------------------------------------*/
namespace Farm {
class Animal {
public:
    /* Enum definiton. */
    enum AnimalError {
        AnimalNoError,
        AnimalAlreadyFed,
        AnimalNotExist,
        AnimalAgeNotAdequate,
        AnimalIsOutdoor,
        AnimalIsIndoor,
        AnimalAlreadyWentOutdoorToday,
        AnimalHappyIndexAlert,
        AnimalAlreadyTrainedToday,
        AnimalNotSupportedTraining
    };

    typedef std::vector<Animal *> AnimalList;

    /* Lift time declaration. Units in Days. */
    static constexpr uint16_t CHICKEN_LIFE_TIME = 15;
    static constexpr uint16_t CAT_LIFE_TIME = 20;
    static constexpr uint16_t DOG_LIFE_TIME = 25;
    static constexpr uint16_t PIG_LIFE_TIME = 22;
    static constexpr uint16_t DEFAULT_AGE = 0;

    /* Max Weight. Units in Kg. */
    static constexpr double CHICKEN_MAX_WEIGHT = 2;
    static constexpr double CAT_MAX_WEIGHT = 4;
    static constexpr double DOG_MAX_WEIGHT = 7;
    static constexpr double PIG_MAX_WEIGHT = 10;

    /* Weight Gain. Units in Kg. */
    static constexpr double CHICKEN_GAIN_WEIGHT = 0.2;
    static constexpr double CAT_GAIN_WEIGHT = 1;
    static constexpr double DOG_GAIN_WEIGHT = 1;
    static constexpr double PIG_GAIN_WEIGHT = 1;

    /* Condition for Gain Weight. Units in Days. */
    static constexpr uint16_t CHICKEN_WEIGHT_CONSECUTIVE_DAYS = 2;
    static constexpr uint16_t CAT_WEIGHT_CONSECUTIVE_DAYS = 3;
    static constexpr uint16_t DOG_WEIGHT_CONSECUTIVE_DAYS = 2;
    static constexpr uint16_t PIG_WEIGHT_CONSECUTIVE_DAYS = 1;

    /* Happy Index. Pigs don't have this index. */
    static constexpr int8_t HAPPY_INDEX_MAX = 10;
    static constexpr int8_t HAPPY_INDEX_MIN = 0;
    static constexpr int8_t HAPPY_INDEX_DEFAULT = 7;
    static constexpr int8_t GAIN_HAPPY_INDEX = 2;

    /* Intelligent Index. Only Dog has this index. */
    static constexpr int8_t INTELLIGENT_INDEX_MAX = 10;
    static constexpr int8_t INTELLIGENT_INDEX_MIN = 0;
    static constexpr int8_t INTELLIGENT_INDEX_DEFAULT = 0;
    static constexpr int8_t INTELLIGENT_INDEX_GAIN_SELL_PRICE = 10;
    static constexpr int8_t INTELLIGENT_INDEX_REPRODUCIBLE = 10;
    static constexpr int8_t INTELLIGENT_INDEX_NOT_APPLICABLE = -1;
    static constexpr int8_t INTELLIGENT_GAIN_FACTOR = 2;

    /* Prices. Units in USD. */
    static constexpr uint16_t CHICKEN_SELL_PRICE = 2;          /* Per unit */
    static constexpr uint16_t CAT_SELL_PRICE = 2;              /* Per unit */
    static constexpr uint16_t DOG_SELL_PRICE = 5;              /* Per unit */
    static constexpr uint16_t DOG_INTELLIGENT_SELL_PRICE = 10; /* Per unit */
    static constexpr uint16_t PIG_SELL_PRICE = 1;              /* Per kg */

    /* Condition to sell. */
    static constexpr double CHICKEN_WEIGHT_TO_SELL = 2;
    static constexpr uint16_t CAT_AGE_TO_SELL = 10;
    static constexpr uint16_t DOG_AGE_TO_SELL = 12;
    static constexpr uint16_t PIG_AGE_TO_SELL = 5;

    /* Buying. */
    static constexpr uint16_t CHICKEN_BUY_PRICE = 4;
    static constexpr uint16_t CAT_BUY_PRICE = 7;
    static constexpr uint16_t DOG_BUY_PRICE = 8;
    static constexpr uint16_t PIG_BUY_PRICE = 6;

    /* Sound. */
    static constexpr const char *CHICKEN_SOUND = "Bawk!";
    static constexpr const char *CAT_SOUND = "Meow!";
    static constexpr const char *DOG_SOUND = "Woof!";
    static constexpr const char *PIG_SOUND = "Oink!";

    /* Time to sound. */
    static constexpr int CHICKEN_SOUND_TIME = 6;
    static constexpr int CAT_SOUND_TIME = 1;
    static constexpr int DOG_SOUND_TIME = 20;
    static constexpr int PIG_SOUND_TIME = 0; /* If hungry. */

    /* Happy index reduction by sounds. */
    static constexpr int CHICKEN_HAPPY_INDEX_REDUCTION_BY_SOUND = 1;
    static constexpr int CAT_HAPPY_INDEX_REDUCTION_BY_SOUND = 1;
    static constexpr int DOG_HAPPY_INDEX_REDUCTION_BY_SOUND = 1;
    static constexpr int HAPPY_INDEX_NOT_APPLICABLE = -1;

    /* Condition to reduce happy index by sounds. */
    static constexpr int CHICKEN_REDUCTION_CONDITION_BY_SOUND =
        10; /* From Cats, Dogs and Pigs in a day. */
    static constexpr int CAT_REDUCTION_CONDITION_BY_SOUND =
        15; /*From Dogs and Chickens in a day. */
    static constexpr int DOG_REDUCTION_CONDITION_BY_SOUND =
        5; /* From Cats in a day. */

    /* Eating. */
    static constexpr int CHICKEN_EAT_UNIT = 1;
    static constexpr int CAT_EAT_UNIT = 2;
    static constexpr int DOG_EAT_UNIT = 3;
    static constexpr int PIG_EAT_UNIT = 7;

    static constexpr int ANIMAL_EAT_SOUND = 1;

    /* Condition to eat. */
    static constexpr uint16_t CHICKEN_AGE_TO_EAT = 0;
    static constexpr uint16_t CAT_AGE_TO_EAT = 2;
    static constexpr uint16_t DOG_AGE_TO_EAT = 3;
    static constexpr uint16_t PIG_AGE_TO_EAT = 2;

    /* Number of Children. */
    static constexpr uint8_t CHICKEN_NUM_REPRODUCE_RANDOM_MIN = 1;
    static constexpr uint8_t CHICKEN_NUM_REPRODUCE_RANDOM_MAX = 3;
    static constexpr uint8_t CAT_NUM_REPRODUCE = 1;
    static constexpr uint8_t DOG_NUM_REPRODUCE = 1;
    static constexpr uint8_t PIG_NUM_REPRODUCE_RANDOM_MIN = 1;
    static constexpr uint8_t PIG_NUM_REPRODUCE_RANDOM_MAX = 2;

    /* Time to reproduce. */
    static constexpr uint16_t CHICKEN_AGE_TO_REPRODUCE = 13;
    static constexpr uint16_t CAT_AGE_TO_REPRODUCE = 18;
    static constexpr uint16_t DOG_AGE_TO_REPRODUCE = 22;
    static constexpr uint16_t PIG_AGE_TO_REPRODUCE = 20;

    /* Condition to reproduce. */
    static constexpr uint8_t CHICKEN_WEIGHT_TO_REPRODUCE = 2;
    static constexpr uint8_t CAT_WEIGHT_TO_REPRODUCE = 4;
    static constexpr uint8_t DOG_WEIGHT_TO_REPRODUCE = 7;
    static constexpr uint8_t PIG_WEIGHT_TO_REPRODUCE = 10;

    static constexpr uint8_t CHICKEN_HAPPY_INDEX_TO_REPRODUCE = 10;
    static constexpr uint8_t CAT_HAPPY_INDEX_TO_REPRODUCE = 10;
    static constexpr uint8_t DOG_HAPPY_INDEX_TO_REPRODUCE = 10;

    static constexpr uint8_t DOG_INTELLIGENT_INDEX_TO_REPRODUCE = 10;

    /* Baby animal sound when it is born. */
    static constexpr uint8_t CHICKEN_NUM_SOUND_WHEN_BORN = 3;
    static constexpr uint8_t CAT_NUM_SOUND_WHEN_BORN = 2;
    static constexpr uint8_t DOG_NUM_SOUND_WHEN_BORN = 1;
    static constexpr uint8_t PIG_NUM_SOUND_WHEN_BORN = 2;

    /* Go out. */
    static constexpr int TIME_TO_GO_BACK = 0; /* 11:59PM. Except Cat */
    static constexpr int TIME_TO_GO_OUT_BEGIN =
        4; /* Applicable only for Chickens & Dogs. */
    static constexpr int TIME_TO_GO_OUT_END =
        0; /* Applicable only for Chickens & Dogs. */
    static constexpr int NOT_GO_OUT_CONSECUTIVE = 2;
    static constexpr int GAIN_ON_CONSECUTIVE_INDOOR = -1;
    static constexpr int HAPPY_INDEX_CONDITION_TO_EAT = 3;

    /* Die. */
    static constexpr int DIE_WHEN_HAPPY_INDEX_ZERO = 3;
    static constexpr int CHICKEN_NUM_SOUND_WHEN_DIE = 4;
    static constexpr int CAT_NUM_SOUND_WHEN_DIE = 4;
    static constexpr int DOG_NUM_SOUND_WHEN_DIE = 2;
    static constexpr int PIG_NUM_SOUND_WHEN_DIE = 3;

    /* Train for Dog. */
    static constexpr int DOG_TRAIN_FACTOR = 2;

    /* Children naming. */
    static constexpr int CHILDREN_NAMING_NUMBER = 2;
    static constexpr const char *CHILDREN_NAMING = "_child+";

protected:
    std::string mName;
    uint16_t mAge;
    double mWeight;
    int mFeedConsecutiveDays;
    SharedObjects &mShared;
    bool mIsOutdoor;
    int mNotGoOutdoorConsecutiveDays;
    bool mIsWentOutToday;
    int mZeroHappyIndexConsecutiveDays;
    bool mFedToday = false;
    AnimalType mType;
    std::map<AnimalType, int> numOfSounds;
    int mHappyIndex;
    int mChildrenRemark;
    int mIntelligentIndex;
    bool isTrainedToday;

public:
    static const std::unordered_map<AnimalError, std::string>
        AnimalErrorToStrings;

    static const std::unordered_map<AnimalType, std::string>
        AnimalTypeToStrings;

    Animal(std::string Name, SharedObjects &shared);
    virtual ~Animal();
    const std::string getName(void) const;
    uint16_t getAge(void) const;
    virtual void incAge(void);
    virtual bool exceedLifeTime(void) = 0;
    AnimalError feedAnimal(void);
    virtual void scanAnimal(void) = 0;
    double getWeight(void);
    int getFeedConsecutiveDays(void);
    bool getFedToday(void);
    virtual bool isSalable(void) const = 0;
    virtual void killAnimal(void) = 0;
    virtual int getSellPrice(void) const = 0;
    virtual AnimalType getType(void) const = 0;
    void clearSound(void);
    void gainSound(AnimalType type, int num);
    virtual int checkHappyReductionBySounds(void) = 0;
    std::string getSoundStatusStrings(void);
    virtual void sound(int NumOfSound = 1) = 0;
    virtual bool isReproducible(void) = 0;
    int reproduce(AnimalList &childList);
    virtual Animal *reproduce(std::string name) const = 0;
    virtual int getNumberOfChilds(void) = 0;
    virtual void soundWhenBorn(void) = 0;
    AnimalError letAnimalGoOut(void);
    AnimalError letAnimalGoBack(void);
    bool getGoOutStatus(void);
    static std::string animalTypeToString(AnimalType type);
    int gainHappyIndex(int offset);
    int getHappyIndex(void);
    int getZeroHappyIndexConsecutiveDays(void);
    bool isDead(void);
    virtual int gainIntelligentIndex(int offset) = 0;
    virtual int getIntelligentIndex(void) const = 0;
    virtual AnimalError trainAnimal(void) = 0;

protected:
    virtual AnimalError isEdible(void) = 0;
};
}; // namespace Farm

#endif
