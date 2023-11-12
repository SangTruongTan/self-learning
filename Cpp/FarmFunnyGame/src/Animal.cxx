#include "Animal.h"

Farm::Animal::Animal(Farm::Logger *Log, const char *Name, Farm::SharedObjects &shared)
    : mLogger(Log), mName(Name), mAge(0), mWeight(0), mFeedConsecutiveDays(0),
      mGoOutStatus(false), mShared(shared) {
    std::stringstream ss;
    ss << "New Animal named: " << mName;
    this->mLogger->LogD(ss.str());
}

Farm::Animal::~Animal() {
    this->mLogger->LogD("This animal will be dead");
}
