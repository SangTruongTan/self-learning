#include "MacDonald.h"

#include <thread>

Farm::MacDonald::MacDonald(Farm::Logger *Log)
    : mLogger(Log), mTimeManager(nullptr) {
    this->mLogger->LogI("New Mac Donal Farm has been created");
}

void Farm::MacDonald::start() {
    this->mLogger->LogI("Create new time manager");
    this->mTimeManager = new TimeManager(this->mLogger);
    std::cout << "Buy a new chicken" << std::endl;
    this->mAnimalList.push_back(
        new Chicken(this->mLogger, "Cho", this->mShared));

    std::vector<std::pair<int, std::function<void(void)>>> timeLists;
    timeLists.push_back(std::make_pair(0, [this]() {
        std::cout << "this is 12AM" << std::endl;
        this->incAgeAll();
    }));
    std::thread timeThread(std::bind(&TimeManager::start, this->mTimeManager, std::ref(timeLists)));
    this->mLogger->LogI("Spawned a new thread for Time Managers");
    timeThread.join();
}

void Farm::MacDonald::incAgeAll() {
    this->mLogger->LogI("Increase age for all animals");
    for (auto const &animal : this->mAnimalList) {
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
