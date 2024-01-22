#include "Animal.h"

namespace Farm {

Animal::Animal(std::string Name, SharedObjects &shared)
    : mName(Name), mAge(0), mWeight(0), mFeedConsecutiveDays(0),
      mGoOutStatus(false), mShared(shared) {
    std::stringstream ss;
    ss << "New Animal named: " << mName;
    LOG_ANIMAL(LogLevel::DEBUG, ss.str());
}

Animal::~Animal() {
    LOG_ANIMAL(LogLevel::DEBUG, "This animal will be dead");
}

const std::string Animal::getName(void) const {
    return this->mName;
}

const uint16_t Animal::getAge(void) const {
    return this->mAge;
}

void Animal::incAge() {
    std::stringstream ss;
    ss << "[" << this->mName << "] Inc Age to => " << ++this->mAge;
    LOG_ANIMAL(LogLevel::INFO, ss.str());
}
} // namespace Farm
