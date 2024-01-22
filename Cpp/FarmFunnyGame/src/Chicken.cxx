#include "Chicken.h"

namespace Farm {

Chicken::Chicken(std::string Name, SharedObjects &shared)
    : Animal(Name, shared) {
    std::stringstream ss;
    ss << "A new Chicken named: \"" << this->mName << "\" has been born";
    LOG_ANIMAL(LogLevel::INFO, ss.str());
}

Chicken::~Chicken() {
    this->sound(Animal::CHICKEN_NUM_SOUND_WHEN_DIE);
    std::stringstream ss;
    ss << "\"" << this->mName << "\" has been died!";
    LOG_ANIMAL(LogLevel::INFO, ss.str());
    LOG_CONSOLE(LogLevel::INFO, ss.str().c_str(), "\n");
}

void Chicken::sound(int NumOfSound) {
    for (int i = 0; i < NumOfSound; i++) {
        this->mShared.ChickenSound++;
        LOG_ANIMAL(LogLevel::INFO, std::string(CHICKENS_SOUND));
        LOG_CONSOLE(LogLevel::INFO, CHICKENS_SOUND, "\n");
    }
}

bool Chicken::exceedLifeTime(void) {
    bool retVal = false;
    if (this->getAge() >= Animal::CHICKEN_LIFE_TIME) {
        retVal = true;
    }
    return retVal;
}
} // namespace Farm
