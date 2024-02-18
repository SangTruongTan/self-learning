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

MacDonald::MacDonald() : mTimeManager(nullptr), mUserInterface(nullptr) {
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
        std::stringstream ss;
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
                std::stringstream ss;
                const auto typeIt = AnimalTypeFromStrings.find(cmd.at(1));
                if (typeIt != AnimalTypeFromStrings.end()) {
                    ss << "CMD --> feed " << cmd.at(1);
                    LOG_FARM(LogLevel::INFO, ss.str().c_str());
                    feedAnimals(typeIt->second);
                } else {
                    ss << "CMD --> feed [" << cmd.at(1) << "]";
                    LOG_FARM(LogLevel::INFO, ss.str().c_str());
                    feedAnimals(AnimalType::SPECIFIC_ANIMAL, cmd.at(1));
                }
            } else if (cmd.at(0) == "let") {
                if (cmd.size() == 3) {
                    if (cmd.at(2) == "out") {
                        if (cmd.at(2) == "animals") {
                            LOG_FARM(LogLevel::INFO, "CMD --> let animals out");
                        } else if (cmd.at(2) == "chickens") {
                            LOG_FARM(LogLevel::INFO,
                                     "CMD --> let chickens out");
                        } else if (cmd.at(2) == "cats") {
                            LOG_FARM(LogLevel::INFO, "CMD --> let cats out");
                        } else if (cmd.at(2) == "dogs") {
                            LOG_FARM(LogLevel::INFO, "CMD --> let dogs out");
                        } else if (cmd.at(2) == "pigs") {
                            LOG_FARM(LogLevel::INFO, "CMD --> let dogs out");
                        } else {
                            LOG_FARM(LogLevel::INFO,
                                     "CMD --> let specific animal out");
                        }
                    } else if (cmd.at(2) == "back") {
                        if (cmd.at(2) == "animals") {
                            LOG_FARM(LogLevel::INFO,
                                     "CMD --> let animals back");
                        } else if (cmd.at(2) == "chickens") {
                            LOG_FARM(LogLevel::INFO,
                                     "CMD --> let chickens back");
                        } else if (cmd.at(2) == "cats") {
                            LOG_FARM(LogLevel::INFO, "CMD --> let cats back");
                        } else if (cmd.at(2) == "dogs") {
                            LOG_FARM(LogLevel::INFO, "CMD --> let dogs back");
                        } else if (cmd.at(2) == "pigs") {
                            LOG_FARM(LogLevel::INFO, "CMD --> let dogs back");
                        } else {
                            LOG_FARM(LogLevel::INFO,
                                     "CMD --> let specific animal back");
                        }
                    } else {
                        LOG_CONSOLE(LogLevel::INFO,
                                    "Command doesn't support --> You must "
                                    "specify \"out\" or \"back\"\n");
                    }
                }
            } else if (cmd.at(0) == "buy") {
                if (cmd.size() >= 3) {
                    std::stringstream ss;
                    const auto typeIt = AnimalTypeFromStrings.find(cmd.at(1));
                    if (typeIt != AnimalTypeFromStrings.end()) {
                        ss << "CMD --> buy "
                           << AnimalStrings.at((*typeIt).second) << " named:";
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
                        LOG_CONSOLE(
                            LogLevel::INFO,
                            "Command doesn't support --> You must choose one "
                            "of animal types (chickens|cats|dogs|pigs)\n");
                    }
                } else {
                    LOG_CONSOLE(LogLevel::INFO, "Command doesn't support\n");
                }
            } else if (cmd.at(0) == "sell") {
                if (cmd.size() >= 2) {
                    std::stringstream ss;
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
                        std::stringstream ss;
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
    std::vector<std::string> removeList{};
    if (this->mAnimalList.size() > 0) {
        LOG_FARM(LogLevel::DEBUG, "Checking animal's age");
        for (Animal *animal : mAnimalList) {
            if (animal->exceedLifeTime()) {
                std::ostringstream os;
                os << "Animal[" << animal->getName() << "] Exceeded life time";
                LOG_FARM(LogLevel::INFO, os.str());
                animal->killAnimal();
                removeList.emplace_back(animal->getName());
            }
        }
        removeAnimals(removeList);
    }
}

Animal *MacDonald::isAnimalExist(const char *name) {
    Animal *retval{nullptr};
    for (Animal *ani : this->mAnimalList) {
        LOG_FARM(LogLevel::INFO, ani->getName().c_str());
        if (::strcmp(ani->getName().c_str(), name) == 0) {
            std::stringstream ss;
            ss << "Found (" << name << ") in Animal List";
            LOG_FARM(LogLevel::INFO, ss.str().c_str());
            retval = ani;
        }
    }
    return retval;
}

const char *MacDonald::getAnimalName(Animal *ani) const {
    if (dynamic_cast<Chicken *>(ani) != nullptr) {
        return MacDonald::CHICKEN_NAME;
    }
    return MacDonald::ANIMAL_NAME;
}

void MacDonald::reportAnimals() const {
    LOG_CONSOLE(LogLevel::INFO, "Animals status\n");
    LOG_CONSOLE(LogLevel::INFO, getAnimalsStatus());
}

void MacDonald::buyAnimal(AnimalType type,
                          std::vector<std::string>::iterator start,
                          std::vector<std::string>::iterator end) {
    std::stringstream ss;
    for (auto i = start; i != end; i++) {
        ss.clear();
        ss.str(std::string());
        if (this->isAnimalExist((*i).c_str()) == nullptr) {
            bool retval = true;
            switch (type) {
            case AnimalType::CHICKEN:
                this->mAnimalList.emplace_back(
                    new Chicken((*i).c_str(), this->mShared));
                break;
            case AnimalType::CAT:
            case AnimalType::PIG:
            case AnimalType::DOG:
            case AnimalType::ANIMAL:
            case AnimalType::SPECIFIC_ANIMAL:
                LOG_CONSOLE(LogLevel::INFO, "Animal doesn't support yet\n");
                retval = false;
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

    /* Reproduction handling. */
    timeLists.push_back(std::make_pair(0, [this]() {
        std::lock_guard<std::mutex> lock(this->mMutexAnimals);
        this->AnimalReproduction();
    }));

    /* Check at specific moment. */
    /* Time to sound. */
    /* Cats. */
    timeLists.push_back(std::make_pair(
        static_cast<const int>(Animal::CAT_SOUND_TIME), [this]() {
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
    timeLists.push_back(std::make_pair(
        static_cast<const int>(Animal::CHICKEN_SOUND_TIME), [this]() {
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
    timeLists.push_back(std::make_pair(
        static_cast<const int>(Animal::DOG_SOUND_TIME), [this]() {
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
    timeLists.push_back(std::make_pair(
        static_cast<const int>(Animal::PIG_SOUND_TIME), [this]() {
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
    timeLists.push_back(
        std::make_pair(static_cast<const int>(TimeManager::CONTINUOUS), [this] {
            std::lock_guard<std::mutex> lock(this->mMutexAnimals);
            this->updateDashboard();
        }));
}

void MacDonald::feedAnimals(AnimalType Type, std::string name) {
    if (mAnimalList.size() == 0) {
        std::string er = "Farm is empty";
        LOG_FARM(LogLevel::INFO, er.c_str());
        LOG_CONSOLE(LogLevel::INFO, er.c_str(), "\n");
        return;
    }
    Animal::AnimalError ae{Animal::AnimalError::AnimalNoError};
    if (Type == AnimalType::ANIMAL) {
        LOG_FARM(LogLevel::INFO, "Feed all animals");
        for (Animal *animal : this->mAnimalList) {
            ae = animal->feedAnimal();
            LOG_CONSOLE(LogLevel::INFO, "Feed Animal [", animal->getName(),
                        "] <= ", AnimalErrorToStrings(ae), "\n");
        }
    } else if (Type == AnimalType::CHICKEN) {
        LOG_FARM(LogLevel::INFO, "Feed all chickens");
        for (Animal *animal : this->mAnimalList) {
            if (dynamic_cast<Chicken *>(animal) != nullptr) {
                ae = animal->feedAnimal();
                LOG_CONSOLE(LogLevel::INFO, "Feed Chicken [", animal->getName(),
                            "] <= ", AnimalErrorToStrings(ae), "\n");
            }
        }
    } else if (Type == AnimalType::PIG) {
        LOG_CONSOLE(LogLevel::INFO, "Not support yet");
    } else if (Type == AnimalType::DOG) {
        LOG_CONSOLE(LogLevel::INFO, "Not support yet");
    } else if (Type == AnimalType::CAT) {
        LOG_CONSOLE(LogLevel::INFO, "Not support yet");
    } else if (Type == AnimalType::SPECIFIC_ANIMAL) {
        LOG_FARM(LogLevel::INFO, "Try feeding [", name, "]");
        Animal *ani{nullptr};
        if ((ani = isAnimalExist(name.c_str())) != nullptr) {
            ae = ani->feedAnimal();
            LOG_CONSOLE(LogLevel::INFO, "Feed [", ani->getName(),
                        "] <= ", AnimalErrorToStrings(ae), "\n");
        } else {
            ae = Animal::AnimalError::AnimalNotExist;
            std::stringstream msg;
            msg << "Feeding failed [" << name << "] does not exist"
                << std::endl;
            LOG_FARM(LogLevel::INFO, msg.str());
            LOG_CONSOLE(LogLevel::INFO, msg.str(), "\n");
        }
    }
}

std::string MacDonald::AnimalErrorToStrings(Animal::AnimalError er) {
    return Animal::AnimalErrorToStrings.at(er);
}

void MacDonald::updateDashboard(void) const {
    static int numOfLines{0};
    std::stringstream ss;
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
    VariadicTable<std::string, const char *, const uint16_t, double, int,
                  std::string, std::string>
        vt({"Name", "Type", "Age", "Weight", "FedDays", "FedToday",
            "SoundHeard"},
           10);
    for (Animal *animal : this->mAnimalList) {
        vt.addRow(animal->getName(), getAnimalName(animal), animal->getAge(),
                  animal->getWeight(), animal->getFeedConsecutiveDays(),
                  (animal->getFedToday() == false) ? "False" : "True",
                  animal->getSoundStatusStrings());
    }
    std::stringstream ss;
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
                std::stringstream ss;
                ss << "Sold [" << ani->getName() << "] earned "
                   << ani->getSellPrice() << " " << CURRENCY << std::endl;
                LOG_FARM(LogLevel::INFO, ss.str());
                LOG_CONSOLE(LogLevel::INFO, ss.str());
                std::vector<std::string> removeList{ani->getName()};
                removeAnimals(removeList);
                retval |= true;
            }
        } else {
            std::stringstream msg;
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
    std::stringstream ss;
    for (Animal *animal : mAnimalList) {
        int num = animal->reproduce(childList);
        if (num != 0) {
            ss.clear();
            ss.str(std::string());
            ss << "["  << animal->getName() << "] reproduced " << num << " child(s)" << std::endl;
            LOG_FARM(LogLevel::INFO, ss.str());
            LOG_CONSOLE(LogLevel::INFO, ss.str());
        }
    }
    for (Animal *child : childList) {
        mAnimalList.emplace_back(child);
        child->soundWhenBorn();
    }
}

} // namespace Farm