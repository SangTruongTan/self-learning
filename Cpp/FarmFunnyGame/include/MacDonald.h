#ifndef __MAC_DONALD_H__
#define __MAC_DONALD_H__

#include <condition_variable>
#include <mutex>
#include <sstream>
#include <vector>

#include "Chicken.h"
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

    Farm::TimeManager *mTimeManager;
    Farm::UserInterface *mUserInterface;

    std::mutex mMutexUserInterface;
    std::mutex mMutexAnimals;

    std::vector<std::pair<const int, std::function<void(void)>>> timeLists;

    int mAccountBalance;
    int mFoodUnits;

    const char *getAnimalName(Animal *ani) const;
    void reportAnimals() const;

    void buyAnimal(AnimalType type,
                   std::vector<std::string>::iterator start,
                   std::vector<std::string>::iterator end);
    void registerTimer(void);
    void feedAnimals(AnimalType Type, std::string name = "");
    void scanAnimal(void);
    void updateDashboard(void) const;
    std::string getAnimalsStatus(void) const;
    bool sellAnimals(AnimalType Type, std::string name = "");
    void removeAnimals(std::vector<std::string> nameList);
    bool updateBalance(int offset);
    bool updateFoodUnits(int offset);
    void soundHandler(AnimalType type, int num);

public:
    std::vector<Animal *> mAnimalList;
    Farm::SharedObjects mShared;

    static const std::unordered_map<AnimalType, const char *>
        AnimalStrings;

    static const std::unordered_map<std::string, AnimalType>
        AnimalTypeFromStrings;

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
