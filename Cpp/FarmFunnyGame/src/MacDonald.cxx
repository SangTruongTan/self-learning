#include "MacDonald.h"

#include <thread>

Farm::MacDonald::MacDonald(Farm::Logger *Log)
    : mLogger(Log), mTimeManager(nullptr), mUserInterface(nullptr) {
    this->mLogger->LogI("New Mac Donal Farm has been created");
}

void Farm::MacDonald::start() {
    this->mLogger->LogI("Create new time manager");
    this->mTimeManager = new TimeManager(this->mLogger);

    this->mLogger->LogI("Create a new User Interface attribute");
    this->mUserInterface = new UserInterface(this->mLogger, &this->mIss,
                                             &this->mMutex, &this->mCV);

    std::vector<std::pair<int, std::function<void(void)>>> timeLists;
    timeLists.push_back(std::make_pair(0, [this]() {
        std::cout << "this is 12AM" << std::endl;
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
    while (true) {
        std::unique_lock<std::mutex> lock(this->mMutex);
        this->mCV.wait(lock, [this] { return this->mIss.peek() != EOF; });
        this->mLogger->LogD("Enter parsing process");

        std::string tempString{};
        std::stringstream ss;
        int i{0};
        while (this->mIss.peek() != EOF ) {
            this->mIss >> tempString;
            ss.clear();
            ss.str("");
            ss << "Argument[" << i << "] = " << tempString;
            this->mLogger->LogI(ss.str().c_str());
            i++;
        }
        this->mCV.notify_one();
    }
    this->mLogger->LogI("Exit Farm::MacDonald::handleCommands()");
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
