#ifndef __ANIMAL_H__
#define __ANIMAL_H__

#include <cstdint>
#include <iostream>
#include <string>
#include <sstream>

#include "Logger.h"
#include "SharedObjects.h"

namespace Farm {
class Animal {
public:
    /* Lift time declaration. Units in Days. */
    static constexpr uint16_t CHICKEN_LIFE_TIME = 3;
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

    /* Intelligent Index. Only Dog has this index. */
    static constexpr int8_t INTELLIGENT_INDEX_MAX = 10;
    static constexpr int8_t INTELLIGENT_INDEX_MIN = 0;
    static constexpr int8_t INTELLIGENT_INDEX_DEFAULT = 0;

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
    static constexpr const char *CHICKENS_SOUND = "Bawk!";
    static constexpr const char *CAT_SOUND = "Meow!";
    static constexpr const char *DOG_SOUND = "Woof!";
    static constexpr const char *PIG_SOUND = "Oink!";

    /* Time to sound. */
    static constexpr int CHICKEN_SOUND_TIME = 6;
    static constexpr int CAT_SOUND_TIME = 13;
    static constexpr int DOG_SOUND_TIME = 20;
    static constexpr int Pig_SOUND_TIME = 0; /* If hungry. */

    /* Happy index reduction by sounds. */
    static constexpr int CHICKEN_HAPPY_INDEX_REDUCTION_BY_SOUND = 1;
    static constexpr int CAT_HAPPY_INDEX_REDUCTION_BY_SOUND = 1;
    static constexpr int DOG_HAPPY_INDEX_REDUCTION_BY_SOUND = 1;

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
    static constexpr uint16_t CHICKEN_TIME_TO_REPRODUCE = 13;
    static constexpr uint16_t CAT_TIME_TO_REPRODUCE = 18;
    static constexpr uint16_t DOG_TIME_TO_REPRODUCE = 22;
    static constexpr uint16_t PIG_TIME_TO_REPRODUCE = 20;

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
    static constexpr int TIME_TO_GO_BACK = 12;  /* Except Cat */

    /* Die. */
    static constexpr int DIE_WHEN_HAPPY_INDEX_ZERO = 3;
    static constexpr int CHICKEN_NUM_SOUND_WHEN_DIE = 4;
    static constexpr int CAT_NUM_SOUND_WHEN_DIE = 4;
    static constexpr int DOG_NUM_SOUND_WHEN_DIE = 2;
    static constexpr int PIG_NUM_SOUND_WHEN_DIE = 3;

    /* Train for Dog. */
    static constexpr int DOG_TRAIN_FACTOR = 2;

protected:
    Farm::Logger *mLogger;
    const char *mName;
    uint16_t mAge;
    double mWeight;
    int mFeedConsecutiveDays;
    bool mGoOutStatus;
    Farm::SharedObjects &mShared;
public:
    Animal(Farm::Logger *Log, const char *Name, Farm::SharedObjects &shared);
    virtual ~Animal();
    virtual const char *getName(void) = 0;
    virtual uint16_t getAge(void) = 0;
    virtual void incAge(void) = 0;
    virtual void sound(int NumOfSound = 1) = 0;
    virtual bool exceedLifeTime(void) = 0;

};
}; // namespace Farm

#endif