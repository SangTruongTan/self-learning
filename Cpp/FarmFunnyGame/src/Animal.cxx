#include "Animal.h"

namespace Farm {

Animal::Animal(std::string Name, SharedObjects &shared)
    : mName(Name), mAge(0), mWeight(0), mFeedConsecutiveDays(0),
      mGoOutStatus(false), mShared(shared) {
    std::stringstream ss;
    ss << "New Animal named: " << mName;
    LOG_ANIMAL(LogLevel::DEBUG, ss.str());
}

Animal::~Animal() { LOG_ANIMAL(LogLevel::DEBUG, "This animal will be dead"); }

const std::string Animal::getName(void) const { return this->mName; }

const uint16_t Animal::getAge(void) const { return this->mAge; }

void Animal::incAge() {
    std::stringstream ss;
    ss << "[" << this->mName << "] Inc Age to => " << ++this->mAge;
    LOG_ANIMAL(LogLevel::INFO, ss.str());
}

Animal::AnimalError Animal::feedAnimal(void) {
    AnimalError retval{AnimalAlreadyFed};
    if (mFedToday == false) {
        std::stringstream ss;
        ss << "[" << this->mName << "] Inc feed consecutive days to => "
           << ++mFeedConsecutiveDays;
        LOG_ANIMAL(LogLevel::INFO, ss.str());
        retval = AnimalNoError;
        mFedToday = true;
    }
    return retval;
}

const std::unordered_map<Animal::AnimalError, std::string>
    Animal::AnimalErrorToStrings{{AnimalNoError, "AnimalNoError"},
                                 {AnimalAlreadyFed, "AnimalAlreadyFed"},
                                 {AnimalNotExist, "AnimalNotExist"}};

double Animal::getWeight(void) { return this->mWeight; }

int Animal::getFeedConsecutiveDays(void) { return this->mFeedConsecutiveDays; }

bool Animal::getFedToday(void) { return this->mFedToday; }

} // namespace Farm
