#include "MacDonald.h"

#include <cstring>
#include <thread>

Farm::MacDonald::MacDonald(Farm::Logger *Log)
    : mLogger(Log), mTimeManager(nullptr), mUserInterface(nullptr) {
    this->mLogger->LogI("New Mac Donal Farm has been created");
}

void Farm::MacDonald::start() {
    this->mLogger->LogI("Create new time manager");
    this->mTimeManager = new TimeManager(this->mLogger);

    this->mLogger->LogI("Create a new User Interface attribute");
    this->mUserInterface = new UserInterface(this->mLogger, &this->mMutex);

    std::vector<std::pair<int, std::function<void(void)>>> timeLists;
    timeLists.push_back(std::make_pair(0, [this]() {
        // std::cout << "this is 12AM" << std::endl;
        this->incAgeAll();
    }));
    std::thread timeThread(std::bind(&TimeManager::start, this->mTimeManager,
                                     std::ref(timeLists)));
    this->mLogger->LogI("Spawned a new thread for TimeManager::start()");

    std::thread userInterfaceThread(std::bind(&UserInterface::start, this->mUserInterface));
    this->mLogger->LogI("Spawned a new thread for UserInterface::start()");

    std::thread handleCommandsThread(std::bind(&MacDonald::handleCommands, this));
    this->mLogger->LogI("Spawned a new thread for MacDonald::handleCommands()");

    timeThread.join();
    userInterfaceThread.join();
    handleCommandsThread.join();
}

void Farm::MacDonald::handleCommands() {
    this->mLogger->LogI("Enter Farm::MacDonald::handleCommands()");
    std::vector<std::string> cmd;
    while (true) {
        std::unique_lock<std::mutex> lock(this->mMutex);
        this->mUserInterface->mCV.wait(lock, [this] { return this->mUserInterface->mIss.peek() != EOF; });
        this->mLogger->LogD("Enter parsing process");

        std::string tempString{};
        std::stringstream ss;
        int i{0};
        while (this->mUserInterface->mIss.peek() != EOF ) {
            this->mUserInterface->mIss >> tempString;
            ss.clear();
            ss.str(std::string());
            ss << "Argument[" << i << "] = " << tempString;
            cmd.emplace_back(tempString);
            this->mLogger->LogD(ss.str().c_str());
            i++;
        }
        this->mUserInterface->mCV.notify_one();
        if (cmd.size() <= 1) {
            std::cout << "Command doesn't support" << std::endl;
        } else {
            if (cmd.at(0) == "report") {
                if (cmd.at(1) == "all") {
                    this->mLogger->LogI("CMD --> report all");
                } else if (cmd.at(1) == "resource") {
                    this->mLogger->LogI("CMD --> report resource");
                } else if (cmd.at(1) == "animals") {
                    this->mLogger->LogI("CMD --> report animals");
                } else {
                    std::cout << "Command doesn't support" << std::endl;
                }
            } else if (cmd.at(0) == "feed") {
                if (cmd.at(1) == "animals") {
                    this->mLogger->LogI("CMD --> feed animals");
                } else if (cmd.at(1) == "chickens") {
                    this->mLogger->LogI("CMD --> feed chickens");
                } else if (cmd.at(1) == "cats") {
                    this->mLogger->LogI("CMD --> feed cats");
                } else if (cmd.at(1) == "dogs") {
                    this->mLogger->LogI("CMD --> feed dogs");
                } else if (cmd.at(1) == "pigs") {
                    this->mLogger->LogI("CMD --> feed pigs");
                } else {
                    this->mLogger->LogI("CMD --> feed a specific animal");
                }
            } else if (cmd.at(0) == "let") {
                if (cmd.size() == 3) {
                    if (cmd.at(2) == "out") {
                        if (cmd.at(2) == "animals") {
                            this->mLogger->LogI("CMD --> let animals out");
                        } else if (cmd.at(2) == "chickens") {
                            this->mLogger->LogI("CMD --> let chickens out");
                        } else if (cmd.at(2) == "cats") {
                            this->mLogger->LogI("CMD --> let cats out");
                        } else if (cmd.at(2) == "dogs") {
                            this->mLogger->LogI("CMD --> let dogs out");
                        } else if (cmd.at(2) == "pigs") {
                            this->mLogger->LogI("CMD --> let dogs out");
                        } else {
                            this->mLogger->LogI("CMD --> let specific animal out");
                        }
                    } else if (cmd.at(2) == "back") {
                        if (cmd.at(2) == "animals") {
                            this->mLogger->LogI("CMD --> let animals back");
                        } else if (cmd.at(2) == "chickens") {
                            this->mLogger->LogI("CMD --> let chickens back");
                        } else if (cmd.at(2) == "cats") {
                            this->mLogger->LogI("CMD --> let cats back");
                        } else if (cmd.at(2) == "dogs") {
                            this->mLogger->LogI("CMD --> let dogs back");
                        } else if (cmd.at(2) == "pigs") {
                            this->mLogger->LogI("CMD --> let dogs back");
                        } else {
                            this->mLogger->LogI("CMD --> let specific animal back");
                        }
                    } else {
                        std::cout << "Command doesn't support --> You must specify \"out\" or \"back\"" << std::endl;
                    }
                }
            } else if (cmd.at(0) == "buy") {
                if (cmd.size() == 3) {
                    std::stringstream ss;
                    if (cmd.at(1) == "chickens") {
                        ss << "CMD --> buy chickens named: " << cmd.at(2);
                        this->mLogger->LogI(ss.str().c_str());
                        ss.clear();
                        ss.str(std::string());
                        if (this->isAnimalExist(cmd.at(2).c_str()) == false) {
                            this->mAnimalList.emplace_back(new Farm::Chicken(this->mLogger, cmd.at(2).c_str(), this->mShared));
                            std::cout << "New Chicken (" << cmd.at(2) << ") has been bought" << std::endl;
                        } else {
                            this->mLogger->LogI("This animal has been existed");
                            std::cout << "This animal has been existed" << std::endl;
                        }
                    } else if (cmd.at(1) == "cats") {
                        ss << "CMD --> buy cats named: " << cmd.at(2);
                        this->mLogger->LogI(ss.str().c_str());
                        ss.clear();
                        ss.str(std::string());    
                    } else if (cmd.at(1) == "dogs") {
                        ss << "CMD --> buy dogs named: " << cmd.at(2);
                        this->mLogger->LogI(ss.str().c_str());
                        ss.clear();
                        ss.str(std::string());    
                    } else if (cmd.at(1) == "pigs") {
                        ss << "CMD --> buy pigs named: " << cmd.at(2);
                        this->mLogger->LogI(ss.str().c_str());
                        ss.clear();
                        ss.str(std::string());    
                    } else {
                        std::cout << "Command doesn't support --> You must choose one of animal types (chickens|cats|dogs|pigs)" << std::endl;
                    }
                } else {
                    std::cout << "Command doesn't support" << std::endl;
                }
            } else if (cmd.at(0) == "sell") {
                if (cmd.at(1) == "chickens") {
                    this->mLogger->LogI("CMD --> sell all chickens");
                } else if (cmd.at(1) == "cats") {
                    this->mLogger->LogI("CMD --> sell all cats");
                } else if (cmd.at(1) == "dogs") {
                    this->mLogger->LogI("CMD --> sell all dogs");
                } else if (cmd.at(1) == "pigs") {
                    this->mLogger->LogI("CMD --> sell all pigs");
                } else {
                    this->mLogger->LogI("CMD --> sell a specific animal");
                }
            } else {
                std::cout << "Command doesn't support" << std::endl;
            }
        }
        cmd.clear();
    }
    this->mLogger->LogI("Exit Farm::MacDonald::handleCommands()");
}

void Farm::MacDonald::incAgeAll() {
    this->mLogger->LogI("Increase age for all animals");
    for (Farm::Animal *animal : this->mAnimalList) {
        animal->incAge();
    }
    for (std::vector<Animal *>::iterator animal = this->mAnimalList.begin();
         animal != this->mAnimalList.end();) {
        if ((*animal)->exceedLifeTime() == true) {
            this->mAnimalList.erase(animal);
            delete (*animal);
        } else {
            ++animal;
        }
    }
}

bool Farm::MacDonald::isAnimalExist(const char *name) {
    bool retval = false;
    for (const Farm::Animal *ani : this->mAnimalList) {
        this->mLogger->LogI(ani->getName().c_str());
        if (::strcmp(ani->getName().c_str(), name) == 0) {
            std::stringstream ss;
            ss << "Found (" << name << ") in Animal List"; 
            this->mLogger->LogI(ss.str().c_str());
            retval = true;
        }
    }
    return retval;
}
