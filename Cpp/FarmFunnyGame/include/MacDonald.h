/**
 ******************************************************************************
 * @file           : MacDonald.h
 * @brief          : MacDonald's header file.
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
#ifndef __MAC_DONALD_H__
#define __MAC_DONALD_H__

/* Includes ------------------------------------------------------------------*/
#include <condition_variable>
#include <mutex>
#include <sstream>
#include <vector>

#include "Animal.h"
#include "Logger.h"
#include "SharedObjects.h"
#include "TimeManager.h"
#include "UserInterface.h"

/* Declarations --------------------------------------------------------------*/
namespace Farm {
class MacDonald {
private:
    static constexpr const char *ANIMAL_NAME = "Animal";
    static constexpr const char *CHICKEN_NAME = "Chicken";
    static constexpr const char *DOG_NAME = "Dog";
    static constexpr const char *PIG_NAME = "Pig";
    static constexpr const char *CAT_NAME = "Cat";
    static constexpr const char *CURRENCY = "USD";

    static constexpr int DEFAULT_ACCOUNT_BALANCE = 20;
    static constexpr int DEFAULT_FOOD_UNIT = 50;
    static constexpr int FOOD_FACTOR = 10;

    Farm::TimeManager *mTimeManager;
    Farm::UserInterface *mUserInterface;

    std::mutex mMutexUserInterface;
    std::mutex mMutexAnimals;

    std::vector<std::pair<const int, std::function<void(void)>>> timeLists;

    int mAccountBalance;
    int mFoodUnits;

    void reportAll() const;
    void reportResources() const;
    void reportAnimals() const;

    void buyAnimal(AnimalType type, std::vector<std::string>::iterator start,
                   std::vector<std::string>::iterator end);
    static Animal *buyAnimal(AnimalType type, std::string name,
                             SharedObjects &shared);
    void registerTimer(void);
    void feedAnimals(std::vector<std::string>::iterator begin,
                     std::vector<std::string>::iterator end);
    void feedAnimals(std::string name);
    void feedAnimals(AnimalType Type);
    bool feedAnimals(Animal *animal);
    void scanAnimal(void);
    void updateDashboard(void) const;
    std::string getResourceStatus(void) const;
    std::string getAnimalsStatus(void) const;
    bool sellAnimals(AnimalType Type, std::string name = "");
    void removeAnimals(std::vector<std::string> nameList);
    bool updateBalance(int offset);
    bool updateFoodUnits(int offset);
    void soundHandler(AnimalType type, int num);
    void AnimalReproduction(void);
    void letAnimalGoBackOut(std::vector<std::string>::iterator begin,
                            std::vector<std::string>::iterator end, bool isOut);
    void letAnimalGoBackOut(bool isOut);
    void letAnimalGoBackOut(AnimalType Type, bool isOut);
    void letAnimalGoBackOut(std::string name, bool isOut);
    void letAnimalGoBackOut(Animal *animal, bool isOut);
    void checkAnimalSurvivalCondition(void);
    bool gainBudget(int offset);
    bool checkIfBudgetAdequate(int minus);
    bool gainFoodUnits(int offset);
    bool checkIfFoodAdequate(int minus);
    bool buyFood(std::vector<std::string>::iterator begin);
    std::string happyIndexToString(int index) const;
    AnimalType getSupportedTraining(void);
    void trainAnimals(void);
    void trainAnimals(std::vector<std::string>::iterator begin,
                      std::vector<std::string>::iterator end);
    void trainAnimals(std::string name);
    void trainAnimals(AnimalType type);
    Animal::AnimalError trainAnimals(Animal *animal);
    std::string intelligentIndexToString(int index) const;

public:
    std::vector<Animal *> mAnimalList;
    Farm::SharedObjects mShared;

    static const std::unordered_map<AnimalType, const char *> AnimalStrings;

    static const std::unordered_map<std::string, AnimalType>
        AnimalTypeFromStrings;

    static const std::unordered_map<AnimalType, int> AnimalTypeFoodConsume;

    static const std::unordered_map<AnimalType, int> AnimalTypeToPrice;

    MacDonald();
    void start();
    void handleCommands();

    void incAgeAll();
    Animal *isAnimalExist(const char *name);
    std::string AnimalErrorToStrings(Animal::AnimalError er);
    static int countLines(const std::string &text);
};
}; // namespace Farm

#endif /* __MAC_DONALD_H__ */
