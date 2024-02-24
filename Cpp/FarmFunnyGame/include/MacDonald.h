#ifndef __MAC_DONALD_H__
#define __MAC_DONALD_H__

#include <condition_variable>
#include <mutex>
#include <sstream>
#include <vector>

#include "Animal.h"
#include "Logger.h"
#include "SharedObjects.h"
#include "TimeManager.h"
#include "UserInterface.h"

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
