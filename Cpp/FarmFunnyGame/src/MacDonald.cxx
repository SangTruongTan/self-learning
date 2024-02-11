#include "MacDonald.h"

#include "VariadicTable.h"
#include <algorithm>
#include <cstring>
#include <thread>
#include <typeinfo>

namespace Farm {

const std::unordered_map<Animal::AnimalType, const char *>
    MacDonald::AnimalStrings = {
        {Animal::AnimalType::CHICKEN, MacDonald::CHICKEN_NAME},
        {Animal::AnimalType::PIG, MacDonald::PIG_NAME},
        {Animal::AnimalType::DOG, MacDonald::DOG_NAME},
        {Animal::AnimalType::CAT, MacDonald::CAT_NAME},
        {Animal::AnimalType::ANIMAL, MacDonald::ANIMAL_NAME}};

const std::unordered_map<std::string, Animal::AnimalType>
    MacDonald::AnimalTypeFromStrings = {
        {"chickens", Animal::AnimalType::CHICKEN},
        {"pigs", Animal::AnimalType::PIG},
        {"dogs", Animal::AnimalType::DOG},
        {"cats", Animal::AnimalType::CAT},
        {"animals", Animal::AnimalType::ANIMAL},
};

MacDonald::MacDonald() : mTimeManager(nullptr), mUserInterface(nullptr) {
    LOG_FARM(LogLevel::INFO, "New Mac Donal Farm has been created");
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
                    feedAnimals(Animal::AnimalType::SPECIFIC_ANIMAL, cmd.at(1));
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
    if (this->mAnimalList.size() > 0) {
        std::vector<Animal *>::iterator removeIterator = std::remove_if(
            this->mAnimalList.begin(), this->mAnimalList.end(),
            [this](Animal *animal) {
                LOG_FARM(LogLevel::DEBUG, "Checking animal's age");
                if (animal->exceedLifeTime()) {
                    std::ostringstream os;
                    os << "Animal[" << animal->getName()
                       << "] Exceeded life time";
                    LOG_FARM(LogLevel::INFO, os.str());
                    delete animal;
                    return true; // Remove the animal from the vector
                }
                return false; // Keep the animal in the vector
            });
        this->mAnimalList.erase(removeIterator, this->mAnimalList.end());
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

void MacDonald::buyAnimal(Animal::AnimalType type,
                          std::vector<std::string>::iterator start,
                          std::vector<std::string>::iterator end) {
    std::stringstream ss;
    for (auto i = start; i != end; i++) {
        ss.clear();
        ss.str(std::string());
        if (this->isAnimalExist((*i).c_str()) == nullptr) {
            bool retval = true;
            switch (type) {
            case Animal::AnimalType::CHICKEN:
                this->mAnimalList.emplace_back(
                    new Chicken((*i).c_str(), this->mShared));
                break;
            case Animal::AnimalType::CAT:
            case Animal::AnimalType::PIG:
            case Animal::AnimalType::DOG:
            case Animal::AnimalType::ANIMAL:
            case Animal::SPECIFIC_ANIMAL:
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
    timeLists.push_back(std::make_pair(0, [this]() {
        std::lock_guard<std::mutex> lock(this->mMutexAnimals);
        this->incAgeAll();
    }));

    /* Continuos Executing */
    timeLists.push_back(
        std::make_pair(static_cast<const int>(TimeManager::CONTINUOUS), [this] {
            std::lock_guard<std::mutex> lock(this->mMutexAnimals);
            this->updateDashboard();
        }));
}

void MacDonald::feedAnimals(Animal::AnimalType Type, std::string name) {
    if (mAnimalList.size() == 0) {
        std::string er = "Farm is empty";
        LOG_FARM(LogLevel::INFO, er.c_str());
        LOG_CONSOLE(LogLevel::INFO, er.c_str(), "\n");
        return;
    }
    Animal::AnimalError ae{Animal::AnimalError::AnimalNoError};
    if (Type == Animal::AnimalType::ANIMAL) {
        LOG_FARM(LogLevel::INFO, "Feed all animals");
        for (Animal *animal : this->mAnimalList) {
            ae = animal->feedAnimal();
            LOG_CONSOLE(LogLevel::INFO, "Feed Animal [", animal->getName(),
                        "] <= ", AnimalErrorToStrings(ae), "\n");
        }
    } else if (Type == Animal::AnimalType::CHICKEN) {
        LOG_FARM(LogLevel::INFO, "Feed all chickens");
        for (Animal *animal : this->mAnimalList) {
            if (dynamic_cast<Chicken *>(animal) != nullptr) {
                ae = animal->feedAnimal();
                LOG_CONSOLE(LogLevel::INFO, "Feed Chicken [", animal->getName(),
                            "] <= ", AnimalErrorToStrings(ae), "\n");
            }
        }
    } else if (Type == Animal::AnimalType::PIG) {
        LOG_CONSOLE(LogLevel::INFO, "Not support yet");
    } else if (Type == Animal::AnimalType::DOG) {
        LOG_CONSOLE(LogLevel::INFO, "Not support yet");
    } else if (Type == Animal::AnimalType::CAT) {
        LOG_CONSOLE(LogLevel::INFO, "Not support yet");
    } else if (Type == Animal::AnimalType::SPECIFIC_ANIMAL) {
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
    CLEAN_DASHBOARD();
    LOG_DASHBOARD("DashBoard\n");
    LOG_DASHBOARD(getAnimalsStatus().c_str());
}

std::string MacDonald::getAnimalsStatus(void) const {
    VariadicTable<std::string, const char *, const uint16_t, double, int,
                  std::string>
        vt({"Name", "Type", "Age", "Weight", "FedDays", "FedToday"}, 10);
    for (Animal *animal : this->mAnimalList) {
        vt.addRow(animal->getName(), getAnimalName(animal), animal->getAge(),
                  animal->getWeight(), animal->getFeedConsecutiveDays(),
                  (animal->getFedToday() == false) ? "False" : "True");
    }
    std::stringstream ss;
    vt.print(ss);
    return ss.str();
}

} // namespace Farm