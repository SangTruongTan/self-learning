#include "Chicken.h"

Farm::Chicken::Chicken(Farm::Logger *Log, const char *Name, Farm::SharedObjects &shared)
    : Animal(Log, Name, shared) {
    std::stringstream ss;
    ss << "A new Chicken named: \"" << this->mName << "\" has been born";
    this->mLogger->LogI(ss.str());
}

Farm::Chicken::~Chicken() {
    this->sound(Farm::Animal::DOG_NUM_SOUND_WHEN_DIE);
    std::stringstream ss;
    ss << "\"" << this->mName << "\" has been died!";
    this->mLogger->LogI(ss.str());
    std::cout << ss.str().c_str() << std::endl;
}

const char *Farm::Chicken::getName(void) { return this->mName; }

uint16_t Farm::Chicken::getAge(void) { return this->mAge; }

void Farm::Chicken::incAge() {
    std::stringstream ss;
    ss << "Inc Age to => " << ++this->mAge;
    this->mLogger->LogI(ss.str());
}

void Farm::Chicken::sound(int NumOfSound) {
    for (int i = 0; i < NumOfSound; i++) {
        this->mShared.ChickenSound++;
        this->mLogger->LogI(std::string(CHICKENS_SOUND));
        std::cout << CHICKENS_SOUND << std::endl;
    }
}

bool Farm::Chicken::exceedLifeTime(void) {
    bool retVal = false;
    if (this->getAge() >= Farm::Animal::CHICKEN_LIFE_TIME) {
        retVal = true;
    }
    return retVal;
}
