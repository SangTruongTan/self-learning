#include "MacDonald.h"

#include "VariadicTable.h"
#include <algorithm>
#include <cstring>
#include <thread>
#include <typeinfo>

namespace Farm {

const std::unordered_map<AnimalType, const char *> MacDonald::AnimalStrings = {
    {AnimalType::CHICKEN, MacDonald::CHICKEN_NAME},
    {AnimalType::PIG, MacDonald::PIG_NAME},
    {AnimalType::DOG, MacDonald::DOG_NAME},
    {AnimalType::CAT, MacDonald::CAT_NAME},
    {AnimalType::ANIMAL, MacDonald::ANIMAL_NAME}};

const std::unordered_map<std::string, AnimalType>
    MacDonald::AnimalTypeFromStrings = {
        {"chickens", AnimalType::CHICKEN}, {"pigs", AnimalType::PIG},
        {"dogs", AnimalType::DOG},         {"cats", AnimalType::CAT},
        {"animals", AnimalType::ANIMAL},
};

const std::unordered_map<AnimalType, int> MacDonald::AnimalTypeFoodConsume = {
    {AnimalType::CHICKEN, Animal::CHICKEN_EAT_UNIT},
    {AnimalType::PIG, Animal::PIG_EAT_UNIT},
    {AnimalType::DOG, Animal::DOG_EAT_UNIT},
    {AnimalType::CAT, Animal::CAT_EAT_UNIT}};

const std::unordered_map<AnimalType, int> MacDonald::AnimalTypeToPrice{
    {AnimalType::CHICKEN, Animal::CHICKEN_BUY_PRICE},
    {AnimalType::PIG, Animal::PIG_BUY_PRICE},
    {AnimalType::DOG, Animal::DOG_BUY_PRICE},
    {AnimalType::CAT, Animal::CAT_BUY_PRICE}};

MacDonald::MacDonald()
    : mTimeManager(nullptr), mUserInterface(nullptr),
      mAccountBalance(DEFAULT_ACCOUNT_BALANCE), mFoodUnits(DEFAULT_FOOD_UNIT) {
    LOG_FARM(LogLevel::INFO, "New Mac Donal Farm has been created");
    mShared.soundCallback =
        std::bind(&MacDonald::soundHandler, this, std::placeholders::_1,
                  std::placeholders::_2);
}

void MacDonald::start() {
    LOG_FARM(LogLevel::INFO, "Create new time manager");
    this->mTimeManager = new TimeManager();

    LOG_FARM(LogLevel::INFO, "Create a new User Interface attribute");
    this->mUserInterface = new UserInterface(&this->mMutexUserInterface);

    /* Invoke registerTimer() API*/
    registerTimer();
    std::thread timeThread(std::bind(&TimeManager::start, this->mTimeManager,
                                     std::ref(timeLists)));
    LOG_FARM(LogLevel::INFO, "Spawned a new thread for TimeManager::start()");

    std::thread userInterfaceThread(
        std::bind(&UserInterface::start, this->mUserInterface));
    LOG_FARM(LogLevel::INFO, "Spawned a new thread for UserInterface::start()");

    std::thread handleCommandsThread(
        std::bind(&MacDonald::handleCommands, this));
    LOG_FARM(LogLevel::INFO,
             "Spawned a new thread for MacDonald::handleCommands()");

    timeThread.join();
    userInterfaceThread.join();
    handleCommandsThread.join();
}

void MacDonald::handleCommands() {
    LOG_FARM(LogLevel::INFO, "Enter MacDonald::handleCommands()");
    std::vector<std::string> cmd;
    while (true) {
        std::unique_lock<std::mutex> lock(this->mMutexUserInterface);
        this->mUserInterface->mCV.wait(
            lock, [this] { return this->mUserInterface->mIss.peek() != EOF; });
        LOG_FARM(LogLevel::DEBUG, "Enter parsing process");

        std::string tempString{};
        std::stringstream ss{};
        int i{0};
        static uint16_t cmdCount = 0;
        LOG_CONSOLE(LogLevel::INFO, "\n\n==============\n", cmdCount++,
                    ".User: ", mUserInterface->mIss.str(), "\n");
        LOG_CONSOLE(LogLevel::INFO, "--------------\nMac Donnald: ");
        while (this->mUserInterface->mIss.peek() != EOF) {
            this->mUserInterface->mIss >> tempString;
            ss.clear();
            ss.str(std::string());
            ss << "Argument[" << i << "] = " << tempString;
            cmd.emplace_back(tempString);
            LOG_FARM(LogLevel::DEBUG, ss.str().c_str());
            i++;
        }
        this->mUserInterface->mCV.notify_one();

        if (mUserInterface->mIsPoisonReceived == true) {
            LOG_FARM(
                LogLevel::INFO,
                "The poison signal received. All threads will be canceled");
            mTimeManager->mIsPoisonReceived = true;
            break;
        }

        std::lock_guard<std::mutex> lockAnimal(this->mMutexAnimals);
        if (cmd.size() <= 1) {
            LOG_CONSOLE(LogLevel::INFO, "Command doesn't support\n");
        } else {
            if (cmd.at(0) == "report") {
                if (cmd.at(1) == "all") {
                    LOG_FARM(LogLevel::INFO, "CMD --> report all");

                } else if (cmd.at(1) == "resource") {
                    LOG_FARM(LogLevel::INFO, "CMD --> report resource");
                } else if (cmd.at(1) == "animals") {
                    LOG_FARM(LogLevel::INFO, "CMD --> report animals");
                    reportAnimals();
                } else {
                    LOG_CONSOLE(LogLevel::INFO, "Command doesn't support\n");
                }
            } else if (cmd.at(0) == "feed") {
                std::stringstream ss{};
                ss << "CMD --> ";
                for (std::string str : cmd) {
                    ss << str << " ";
                }
                LOG_FARM(LogLevel::INFO, ss.str());
                feedAnimals(std::next(cmd.begin(), 1), cmd.end());
            } else if (cmd.at(0) == "let") {
                std::stringstream ss{};
                ss << "CMD --> ";
                for (std::string str : cmd) {
                    ss << str << " ";
                }
                LOG_FARM(LogLevel::INFO, ss.str());
                if (cmd.size() >= 3) {
                    std::string sIsOut = cmd.at(cmd.size() - 1);
                    if (sIsOut == "out" || sIsOut == "in") {
                        bool isOut;
                        isOut = (sIsOut == "out") ? true : false;
                        letAnimalGoBackOut(
                            std::next(cmd.begin(), 1),
                            std::next(cmd.begin(), cmd.size() - 1), isOut);
                    }
                } else {
                    LOG_CONSOLE(LogLevel::INFO,
                                "Command doesn't support --> You must "
                                "specify \"out\" or \"back\"\n");
                }
            } else if (cmd.at(0) == "buy") {
                std::string buyErr =
                    "Command doesn't support --> You must choose one "
                    "of animal types (chickens|cats|dogs|pigs) or buy "
                    "food <dollars>\n";
                if (cmd.size() >= 3) {
                    bool isBuyFood = buyFood(std::next(cmd.begin(), 1));
                    if (isBuyFood == false) {
                        std::stringstream ss{};
                        const auto typeIt =
                            AnimalTypeFromStrings.find(cmd.at(1));
                        if (typeIt != AnimalTypeFromStrings.end()) {
                            ss << "CMD --> buy "
                               << AnimalStrings.at((*typeIt).second)
                               << " named:";
                            auto it = std::next(cmd.begin(), 2);
                            if (it < cmd.end()) {
                                auto debugIt = it;
                                while (debugIt != cmd.end()) {
                                    ss << " " << (*debugIt).c_str();
                                    debugIt++;
                                }
                                LOG_FARM(LogLevel::INFO, ss.str().c_str());
                                buyAnimal((*typeIt).second, it, cmd.end());
                            } else {
                                LOG_FARM(LogLevel::ERROR,
                                         "Interator is out of range");
                            }
                        } else {
                            LOG_CONSOLE(LogLevel::INFO, buyErr);
                        }
                    }
                } else {
                    LOG_CONSOLE(LogLevel::INFO, buyErr);
                }
            } else if (cmd.at(0) == "sell") {
                if (cmd.size() >= 2) {
                    std::stringstream ss{};
                    auto typeIt = AnimalTypeFromStrings.find(cmd.at(1));
                    if (typeIt == AnimalTypeFromStrings.end()) {
                        ss << "CMD --> sell animals named:";
                        auto it = std::next(cmd.begin(), 1);
                        if (it < cmd.end()) {
                            while (it != cmd.end()) {
                                sellAnimals(AnimalType::SPECIFIC_ANIMAL,
                                            (*it).c_str());
                                ss << " " << (*it).c_str();
                                it++;
                            }
                            LOG_FARM(LogLevel::INFO, ss.str().c_str());
                        } else {
                            LOG_FARM(LogLevel::ERROR,
                                     "Interator is out of range");
                        }
                    } else {
                        std::stringstream ss{};
                        bool retval;
                        ss << "CMD --> sell Animal Type:";
                        long unsigned int i = 1;
                        std::string typeString;
                        while (i < cmd.size()) {
                            typeString = cmd.at(i++);
                            ss << " " << typeString;
                            typeIt = AnimalTypeFromStrings.find(typeString);
                            if (typeIt != AnimalTypeFromStrings.end()) {
                                retval = sellAnimals(typeIt->second);
                                if (retval == false) {
                                    LOG_CONSOLE(LogLevel::INFO, typeIt->first,
                                                " is not suitable to sell\n");
                                }
                            } else {
                                LOG_CONSOLE(LogLevel::INFO, "{", typeString,
                                            "} is not supported\n");
                            }
                        }
                        LOG_FARM(LogLevel::INFO, ss.str().c_str());
                    }
                } else {
                    LOG_CONSOLE(LogLevel::INFO, "Command doesn't support\n");
                }

                if (cmd.at(1) == "chickens") {
                    LOG_FARM(LogLevel::INFO, "CMD --> sell all chickens");
                } else if (cmd.at(1) == "cats") {
                    LOG_FARM(LogLevel::INFO, "CMD --> sell all cats");
                } else if (cmd.at(1) == "dogs") {
                    LOG_FARM(LogLevel::INFO, "CMD --> sell all dogs");
                } else if (cmd.at(1) == "pigs") {
                    LOG_FARM(LogLevel::INFO, "CMD --> sell all pigs");
                } else {
                    LOG_FARM(LogLevel::INFO, "CMD --> sell a specific animal");
                }
            } else {
                LOG_CONSOLE(LogLevel::INFO, "Command doesn't support\n");
            }
        }
        cmd.clear();
    }
    LOG_FARM(LogLevel::INFO, "Exit MacDonald::handleCommands() thread");
}

void MacDonald::incAgeAll() {
    LOG_FARM(LogLevel::INFO, "Increase age for all animals");
    for (Animal *animal : this->mAnimalList) {
        animal->incAge();
    }
}

Animal *MacDonald::isAnimalExist(const char *name) {
    Animal *retval{nullptr};
    for (Animal *ani : this->mAnimalList) {
        LOG_FARM(LogLevel::INFO, ani->getName().c_str());
        if (::strcmp(ani->getName().c_str(), name) == 0) {
            std::stringstream ss{};
            ss << "Found (" << name << ") in Animal List";
            LOG_FARM(LogLevel::INFO, ss.str().c_str());
            retval = ani;
        }
    }
    return retval;
}

void MacDonald::reportAnimals() const {
    LOG_CONSOLE(LogLevel::INFO, "Animals status\n");
    LOG_CONSOLE(LogLevel::INFO, getAnimalsStatus());
}

void MacDonald::buyAnimal(AnimalType type,
                          std::vector<std::string>::iterator start,
                          std::vector<std::string>::iterator end) {
    std::stringstream ss{};
    for (auto i = start; i != end; i++) {
        ss.clear();
        ss.str(std::string());
        if (this->isAnimalExist((*i).c_str()) == nullptr) {
            bool retval{false};
            int price = AnimalTypeToPrice.at(type);
            if (checkIfBudgetAdequate(price)) {
                Animal *newAnimal = buyAnimal(type, (*i), mShared);
                if (newAnimal != nullptr) {
                    this->mAnimalList.emplace_back(newAnimal);
                    gainBudget(-1 * price);
                    retval = true;
                } else {
                    std::stringstream ss{};
                    ss << "Animal Type {"
                       << Animal::AnimalTypeToStrings.at(type)
                       << "} doesn't supported yet" << std::endl;
                    LOG_FARM(LogLevel::INFO, ss.str());
                    LOG_CONSOLE(LogLevel::INFO, ss.str());
                }
            } else {
                std::stringstream ss{};
                ss << "Account balance requires to buy new {"
                   << Animal::AnimalTypeToStrings.at(type)
                   << "} > Current=" << mAccountBalance
                   << " USD - Price=" << price << " USD" << std::endl;
                LOG_FARM(LogLevel::INFO, ss.str());
                LOG_CONSOLE(LogLevel::INFO, ss.str());
            }
            if (retval == true) {
                LOG_CONSOLE(LogLevel::INFO, "New ", AnimalStrings.at(type),
                            " [", (*i).c_str(), "] has been bought\n");
            }
        } else {
            LOG_FARM(LogLevel::INFO, "This animal [", (*i).c_str(),
                     "] has been existed");
            LOG_CONSOLE(LogLevel::INFO, "This animal [", (*i).c_str(),
                        "] has been existed\n");
        }
    }
}

Animal *MacDonald::buyAnimal(AnimalType type, std::string name,
                             SharedObjects &shared) {
    /* Remark: Add new animals type here. */
    Animal *retval{nullptr};
    switch (type) {
    case AnimalType::CHICKEN:
        retval = new Chicken(name, shared);
        break;
    case AnimalType::CAT:
        retval = new Cat(name, shared);
        break;
    case AnimalType::PIG:
        retval = new Pig(name, shared);
        break;
    case AnimalType::DOG:
    case AnimalType::ANIMAL:
    case AnimalType::SPECIFIC_ANIMAL:
        break;
    }
    return retval;
}

void MacDonald::scanAnimal(void) {
    for (Animal *animal : this->mAnimalList) {
        animal->scanAnimal();
    }
}

void MacDonald::registerTimer(void) {
    /* Check at 12:00AM- */
    timeLists.push_back(std::make_pair(0, [this]() {
        std::lock_guard<std::mutex> lock(this->mMutexAnimals);
        this->scanAnimal();
    }));

    /* Check at 12:00AM+ */
    /* Increase all animal age. */
    timeLists.push_back(std::make_pair(0, [this]() {
        std::lock_guard<std::mutex> lock(this->mMutexAnimals);
        this->incAgeAll();
    }));

    /* Should be checked after scanAnimal & incAgeAll(). */
    timeLists.push_back(std::make_pair(0, [this]() {
        std::lock_guard<std::mutex> lock(this->mMutexAnimals);
        this->checkAnimalSurvivalCondition();
    }));

    /* Reproduction handling. */
    timeLists.push_back(std::make_pair(0, [this]() {
        std::lock_guard<std::mutex> lock(this->mMutexAnimals);
        this->AnimalReproduction();
    }));

    /* Check at specific moment. */
    /* Time to sound. */
    /* Cats. */
    timeLists.push_back(std::make_pair(Animal::CAT_SOUND_TIME, [this]() {
        AnimalType type = AnimalType::CAT;
        std::lock_guard<std::mutex> lock(this->mMutexAnimals);
        LOG_FARM(LogLevel::DEBUG, "It's time to sound for {",
                 Animal::AnimalTypeToStrings.at(type), "}");
        for (Animal *animal : this->mAnimalList) {
            if (animal->getType() == type) {
                animal->sound();
            }
        }
    }));

    /* Chickens. */
    timeLists.push_back(std::make_pair(Animal::CHICKEN_SOUND_TIME, [this]() {
        AnimalType type = AnimalType::CHICKEN;
        std::lock_guard<std::mutex> lock(this->mMutexAnimals);
        LOG_FARM(LogLevel::DEBUG, "It's time to sound for {",
                 Animal::AnimalTypeToStrings.at(type), "}");
        for (Animal *animal : this->mAnimalList) {
            if (animal->getType() == type) {
                animal->sound();
            }
        }
    }));

    /* Dog. */
    timeLists.push_back(std::make_pair(Animal::DOG_SOUND_TIME, [this]() {
        AnimalType type = AnimalType::DOG;
        std::lock_guard<std::mutex> lock(this->mMutexAnimals);
        LOG_FARM(LogLevel::DEBUG, "It's time to sound for {",
                 Animal::AnimalTypeToStrings.at(type), "}");
        for (Animal *animal : this->mAnimalList) {
            if (animal->getType() == type) {
                animal->sound();
            }
        }
    }));

    /* Pigs. */
    timeLists.push_back(std::make_pair(Animal::PIG_SOUND_TIME, [this]() {
        AnimalType type = AnimalType::PIG;
        std::lock_guard<std::mutex> lock(this->mMutexAnimals);
        LOG_FARM(LogLevel::DEBUG, "It's time to sound for {",
                 Animal::AnimalTypeToStrings.at(type), "}");
        for (Animal *animal : this->mAnimalList) {
            if (animal->getType() == type) {
                animal->sound();
            }
        }
    }));

    /* Continuos Executing */
    timeLists.push_back(std::make_pair(TimeManager::CONTINUOUS, [this] {
        std::lock_guard<std::mutex> lock(this->mMutexAnimals);
        this->updateDashboard();
    }));
}

void MacDonald::feedAnimals(std::vector<std::string>::iterator begin,
                            std::vector<std::string>::iterator end) {
    if (mAnimalList.size() == 0) {
        std::string er = "Farm is empty";
        LOG_FARM(LogLevel::INFO, er.c_str());
        LOG_CONSOLE(LogLevel::INFO, er.c_str(), "\n");
        return;
    }
    auto it = begin;
    while (it != end) {
        auto typeIt = AnimalTypeFromStrings.find(*it);
        if (typeIt != AnimalTypeFromStrings.end()) {
            feedAnimals(typeIt->second);
        } else {
            feedAnimals(*it);
        }
        it++;
    }
}

void MacDonald::feedAnimals(std::string name) {
    LOG_FARM(LogLevel::INFO, "Try feeding [", name, "]");
    Animal *ani{nullptr};
    if ((ani = isAnimalExist(name.c_str())) != nullptr) {
        feedAnimals(ani);
    } else {
        std::stringstream msg{};
        msg << "Feeding failed [" << name << "] does not exist" << std::endl;
        LOG_FARM(LogLevel::INFO, msg.str());
        LOG_CONSOLE(LogLevel::INFO, msg.str(), "\n");
    }
}

void MacDonald::feedAnimals(AnimalType Type) {
    LOG_FARM(LogLevel::INFO, "Feed all ", Animal::AnimalTypeToStrings.at(Type));
    for (Animal *animal : this->mAnimalList) {
        if ((animal->getType() == Type) || Type == AnimalType::ANIMAL) {
            if (feedAnimals(animal) != true) {
                break;
            }
        }
    }
}

bool MacDonald::feedAnimals(Animal *animal) {
    bool retval{true};
    Animal::AnimalError ae{Animal::AnimalError::AnimalNoError};
    auto const it = MacDonald::AnimalTypeFoodConsume.find(animal->getType());
    if (it != MacDonald::AnimalTypeFoodConsume.end()) {
        if (checkIfFoodAdequate(it->second)) {
            ae = animal->feedAnimal();
            LOG_CONSOLE(LogLevel::INFO, "Feed [", animal->getName(),
                        "] <= ", AnimalErrorToStrings(ae), "\n");
            if (ae == Animal::AnimalError::AnimalNoError) {
                gainFoodUnits(-1 * (it->second));
            }
        } else {
            std::stringstream ss{};
            ss << "Feeding [" << animal->getName()
               << "] Error => Food warehouse isn't adequate" << std::endl;
            LOG_FARM(LogLevel::ERROR, ss.str());
            LOG_CONSOLE(LogLevel::ERROR, ss.str());
            retval = false;
        }
    } else {
        LOG_FARM(LogLevel::FATAL, "Animal Type isn't supported");
        retval = false;
    }
    return retval;
}

std::string MacDonald::AnimalErrorToStrings(Animal::AnimalError er) {
    return Animal::AnimalErrorToStrings.at(er);
}

void MacDonald::updateDashboard(void) const {
    static int numOfLines{0};
    std::stringstream ss{};
    RESET_CURSOR_DASHBOARD();
    ss << "Farm Resource Balance\n";
    ss << "Account Balance:" << mAccountBalance << " " << CURRENCY
       << "\tFood Units:" << mFoodUnits << " Unit\n\n";
    ss << "DashBoard\n";
    std::string table = getAnimalsStatus();
    ss << table;
    if (countLines(ss.str()) <= numOfLines) {
        CLEAN_DASHBOARD();
    }
    numOfLines = countLines(ss.str());
    LOG_DASHBOARD(ss.str());
}

std::string MacDonald::getAnimalsStatus(void) const {
    VariadicTable<std::string, std::string, const uint16_t, double, int,
                  std::string, std::string, std::string>
        vt({"Name", "Type", "Age", "Weight", "FedDays", "FedToday",
            "GoOutStatus", "HappyIndex"},
           10);
    for (Animal *animal : this->mAnimalList) {
        vt.addRow(animal->getName(),
                  Animal::AnimalTypeToStrings.at(animal->getType()),
                  animal->getAge(), animal->getWeight(),
                  animal->getFeedConsecutiveDays(),
                  (animal->getFedToday() == false) ? "False" : "True",
                  animal->getGoOutStatus() ? "Out" : "In",
                  happyIndexToString(animal->getHappyIndex()));
    }
    std::stringstream ss{};
    vt.print(ss);
    return ss.str();
}

bool MacDonald::sellAnimals(AnimalType Type, std::string name) {
    bool retval{false};
    if (Type == AnimalType::SPECIFIC_ANIMAL) {
        LOG_FARM(LogLevel::INFO, "Try sell [", name, "]");
        Animal *ani{nullptr};
        if ((ani = isAnimalExist(name.c_str())) != nullptr) {
            if (ani->isSalable() == true) {
                updateBalance(ani->getSellPrice());
                std::stringstream ss{};
                ss << "Sold [" << ani->getName() << "] earned "
                   << ani->getSellPrice() << " " << CURRENCY << std::endl;
                LOG_FARM(LogLevel::INFO, ss.str());
                LOG_CONSOLE(LogLevel::INFO, ss.str());
                std::vector<std::string> removeList{ani->getName()};
                removeAnimals(removeList);
                retval |= true;
            }
        } else {
            std::stringstream msg{};
            msg << "Selling failed [" << name << "] does not exist"
                << std::endl;
            LOG_FARM(LogLevel::INFO, msg.str());
            LOG_CONSOLE(LogLevel::INFO, msg.str(), "\n");
        }
    } else {
        auto it = mAnimalList.begin();
        while (it != mAnimalList.end()) {
            if ((*it)->getType() == Type) {
                if (sellAnimals(AnimalType::SPECIFIC_ANIMAL,
                                (*it)->getName()) == true) {
                    retval |= true;
                    continue;
                }
            }
            it++;
        }
    }
    return retval;
}

void MacDonald::removeAnimals(std::vector<std::string> nameList) {
    if (this->mAnimalList.size() > 0) {
        std::vector<Animal *>::iterator removeIterator = std::remove_if(
            this->mAnimalList.begin(), this->mAnimalList.end(),
            [this, nameList](Animal *animal) {
                for (std::string name : nameList) {
                    if (animal->getName() == name) {
                        delete animal;
                        return true; // Remove the animal from the vector
                    }
                }
                return false; // Keep the animal in the vector
            });
        this->mAnimalList.erase(removeIterator, this->mAnimalList.end());
    }
}

bool MacDonald::updateBalance(int offset) {
    bool retval{false};
    int current = mAccountBalance;
    if (mAccountBalance + offset >= 0) {
        mAccountBalance += offset;
        LOG_FARM(LogLevel::INFO, "Balance updated from [", current, "] => [",
                 mAccountBalance, "]");
        retval = true;
    }
    return retval;
}

int MacDonald::countLines(const std::string &text) {
    int lines = 1; // At least one line even if the string is empty

    for (char ch : text) {
        if (ch == '\n') {
            lines++;
        }
    }

    return lines;
}

void MacDonald::soundHandler(AnimalType type, int num) {
    LOG_FARM(LogLevel::DEBUG, "Gain ", num, " sound units from ",
             Animal::AnimalTypeToStrings.at(type));
    for (Animal *animal : this->mAnimalList) {
        LOG_FARM(LogLevel::VERBOSE, "Gain for ", animal->getName());

        animal->gainSound(type, num);
    }
}

void MacDonald::AnimalReproduction(void) {
    std::vector<Animal *> childList{};
    std::stringstream ss{};
    for (Animal *animal : mAnimalList) {
        int num = animal->reproduce(childList);
        if (num != 0) {
            ss.clear();
            ss.str(std::string());
            ss << "[" << animal->getName() << "] reproduced " << num
               << " child(s)" << std::endl;
            LOG_FARM(LogLevel::INFO, ss.str());
            LOG_CONSOLE(LogLevel::INFO, ss.str());
        }
    }
    for (Animal *child : childList) {
        mAnimalList.emplace_back(child);
        child->soundWhenBorn();
    }
}

void MacDonald::letAnimalGoBackOut(std::vector<std::string>::iterator begin,
                                   std::vector<std::string>::iterator end,
                                   bool isOut) {
    LOG_FARM(LogLevel::INFO, "Let all vector animals go ",
             isOut ? "out" : "back");
    auto it = begin;
    while (it != end) {
        const auto typeIt = AnimalTypeFromStrings.find(*it);
        if (typeIt != AnimalTypeFromStrings.end()) {
            if (typeIt->second == AnimalType::ANIMAL) {
                letAnimalGoBackOut(isOut);
                break;
            }
            letAnimalGoBackOut(typeIt->second, isOut);
        } else {
            letAnimalGoBackOut(*it, isOut);
        }
        it++;
    }
}

void MacDonald::letAnimalGoBackOut(bool isOut) {
    LOG_FARM(LogLevel::INFO, "Let all animals go ", isOut ? "out" : "back");
    AnimalType animalType =
        static_cast<AnimalType>(AnimalType::CAT | AnimalType::CHICKEN |
                                AnimalType::DOG | AnimalType::PIG);
    letAnimalGoBackOut(animalType, isOut);
}

/**
 * @brief Let Specific Animal Type Go In/Out.
 * @param Type Type can be multiple animal type.
 */
void MacDonald::letAnimalGoBackOut(AnimalType Type, bool isOut) {
    LOG_FARM(LogLevel::INFO, "Let all {", Animal::animalTypeToString(Type),
             "} go ", isOut ? "out" : "back");
    std::stringstream ss{};
    for (Animal *animal : mAnimalList) {
        if (animal->getType() & Type) {
            letAnimalGoBackOut(animal->getName(), isOut);
        }
    }
}

void MacDonald::letAnimalGoBackOut(std::string name, bool isOut) {
    bool isFound{false};
    for (Animal *animal : mAnimalList) {
        if (animal->getName() == name) {
            LOG_FARM(LogLevel::INFO, "Found [", name, "] to let go ",
                     isOut ? "out" : "back");
            letAnimalGoBackOut(animal, isOut);
            isFound = true;
            break;
        }
    }
    if (isFound == false) {
        std::stringstream ss{};
        ss << "[" << name << "] can not be found" << std::endl;
        LOG_CONSOLE(LogLevel::INFO, ss.str());
        LOG_FARM(LogLevel::INFO, ss.str());
    }
}

void MacDonald::letAnimalGoBackOut(Animal *animal, bool isOut) {
    if (animal->getType() == AnimalType::CHICKEN ||
        animal->getType() == AnimalType::DOG) {
        if (mTimeManager->getHour() < Animal::TIME_TO_GO_OUT_BEGIN) {
            std::stringstream ss{};
            ss << "[" << animal->getName() << " ] can not go out this time"
               << std::endl;
            LOG_FARM(LogLevel::INFO, ss.str());
            LOG_CONSOLE(LogLevel::INFO, ss.str());
            return;
        }
    }

    Animal::AnimalError ae =
        isOut == true ? animal->letAnimalGoOut() : animal->letAnimalGoBack();
    std::stringstream ss{};
    ss << "[" << animal->getName() << "] letAnimalGoOut(" << isOut
       << ") <= " << Animal::AnimalErrorToStrings.at(ae) << std::endl;
    LOG_FARM(LogLevel::DEBUG, ss.str());
    LOG_CONSOLE(LogLevel::DEBUG, ss.str());
}

void MacDonald::checkAnimalSurvivalCondition(void) {
    std::vector<std::string> removeList{};
    if (this->mAnimalList.size() > 0) {
        LOG_FARM(LogLevel::DEBUG, "Checking animal's survival conditions");
        for (Animal *animal : mAnimalList) {
            if (animal->isDead()) {
                std::ostringstream os;
                os << "Animal[" << animal->getName()
                   << "] Exceeded life time or Reached the happy index "
                      "conditions";
                LOG_FARM(LogLevel::INFO, os.str());
                animal->killAnimal();
                removeList.emplace_back(animal->getName());
            }
        }
        removeAnimals(removeList);
    }
}

bool MacDonald::gainBudget(int offset) {
    bool retval{true};
    LOG_FARM(LogLevel::INFO, "Account balance changed ", mAccountBalance,
             " USD => ", mAccountBalance + offset, " USD");
    if (mAccountBalance + offset >= 0) {
        mAccountBalance += offset;
    } else {
        retval = false;
    }
    return retval;
}

bool MacDonald::checkIfBudgetAdequate(int minus) {
    bool retval{true};
    if (mAccountBalance - minus < 0) {
        retval = false;
    }
    return retval;
}

bool MacDonald::gainFoodUnits(int offset) {
    bool retval{true};
    LOG_FARM(LogLevel::INFO, "Food Units changed ", mFoodUnits, " Unit => ",
             mFoodUnits + offset, " Unit");
    if (mFoodUnits + offset >= 0) {
        mFoodUnits += offset;
    } else {
        retval = false;
    }
    return retval;
}

bool MacDonald::checkIfFoodAdequate(int minus) {
    bool retval{true};
    if (mFoodUnits - minus < 0) {
        retval = false;
    }
    return retval;
}

bool MacDonald::buyFood(std::vector<std::string>::iterator begin) {
    bool retval{false};
    if ((*begin) == "food" || (*begin) == "foods") {
        int money = stoi(*std::next(begin, 1));
        std::stringstream ss{};
        if (gainBudget(-1 * money) == false) {
            ss << "Account Balance is not adequate to buy more foods: Current "
                  "= "
               << mAccountBalance << " USD, Requested = " << money << " USD"
               << std::endl;
            LOG_FARM(LogLevel::ERROR, ss.str());
            LOG_CONSOLE(LogLevel::ERROR, ss.str());
        } else {
            int gainFood{money * FOOD_FACTOR};
            gainFoodUnits(gainFood);
            ss << "Bought " << gainFood << " Food Units by " << money << " USD"
               << std::endl;
            LOG_FARM(LogLevel::INFO, ss.str());
            LOG_CONSOLE(LogLevel::INFO, ss.str());
        }
        retval = true;
    }
    return retval;
}

std::string MacDonald::happyIndexToString(int index) const {
    std::string retval{};
    if (index == Animal::HAPPY_INDEX_NOT_APPLICABLE) {
        retval = "NA";
    } else {
        retval = std::to_string(index);
    }
    return retval;
}

} // namespace Farm