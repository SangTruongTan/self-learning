#include "Animal.h"

namespace Farm {

Animal::Animal(std::string Name, SharedObjects &shared)
    : mName(Name), mAge(0), mWeight(0), mFeedConsecutiveDays(0),
      mGoOutStatus(false), mShared(shared), mHappyIndex(HAPPY_INDEX_DEFAULT),
      mChildrenRemark(CHILDREN_NAMING_NUMBER) {
    std::stringstream ss;
    ss << "New Animal named: " << mName;
    LOG_ANIMAL(LogLevel::DEBUG, ss.str());
    numOfSounds[AnimalType::CAT] = 0;
    numOfSounds[AnimalType::CHICKEN] = 0;
    numOfSounds[AnimalType::DOG] = 0;
    numOfSounds[AnimalType::PIG] = 0;
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
    retval = isEdible();
    if (mFedToday == false && retval == AnimalNoError) {
        std::stringstream ss;
        ss << "[" << this->mName << "] Inc feed consecutive days to => "
           << ++mFeedConsecutiveDays;
        LOG_ANIMAL(LogLevel::INFO, ss.str());
        mFedToday = true;
    }

    return retval;
}

const std::unordered_map<Animal::AnimalError, std::string>
    Animal::AnimalErrorToStrings{
        {AnimalNoError, "AnimalNoError"},
        {AnimalAlreadyFed, "AnimalAlreadyFed"},
        {AnimalNotExist, "AnimalNotExist"},
        {AnimalAgeNotAdequate, "AnimalAgeNotAdequate"}};

const std::unordered_map<AnimalType, std::string> Animal::AnimalTypeToStrings{
    {AnimalType::ANIMAL, "ANIMAL"},
    {AnimalType::CAT, "CAT"},
    {AnimalType::DOG, "DOG"},
    {AnimalType::CHICKEN, "CHICKEN"},
    {AnimalType::PIG, "PIG"},
    {AnimalType::SPECIFIC_ANIMAL, "SPECIFIC_ANIMAL"}};

double Animal::getWeight(void) { return this->mWeight; }

int Animal::getFeedConsecutiveDays(void) { return this->mFeedConsecutiveDays; }

bool Animal::getFedToday(void) { return this->mFedToday; }

void Animal::clearSound(void) {
    LOG_ANIMAL(LogLevel::INFO, "[", mName, "] Clear all sounds heard today");
    auto it = numOfSounds.begin();
    while (it != numOfSounds.end()) {
        it->second = 0;
    }
}

void Animal::gainSound(AnimalType type, int num) {
    numOfSounds.at(type) += num;
    LOG_ANIMAL(LogLevel::INFO, "[", mName, "] gain ", num, " sounds from ",
               Animal::AnimalTypeToStrings.at(type), " => ",
               numOfSounds.at(type));
}

std::string Animal::getSoundStatusStrings(void) {
    std::stringstream ss;
    auto it = numOfSounds.begin();
    while (it != numOfSounds.end()) {
        if ((it->first != AnimalType::ANIMAL) &&
            (it->first != AnimalType::SPECIFIC_ANIMAL)) {
            ss << AnimalTypeToStrings.at(it->first) << "=" << it->second << "|";
        }
        it++;
    }
    return ss.str();
}

int Animal::reproduce(AnimalList &childList) {
    int retval{0};
    std::stringstream name;
    if (isReproducible() == false) {
        LOG_ANIMAL(LogLevel::DEBUG, "[", mName,
                   "]'s condition hasn't been appropriate to reproduce");
    } else {
        int num = getNumberOfChilds();
        LOG_ANIMAL(LogLevel::INFO, "[", mName,
                   "] met condition to reproduce => ", num, " child(s)");
        for (int i = 0; i < num; i++) {
            name.clear();
            name.str(std::string());
            name << mName << Animal::CHILDREN_NAMING << mChildrenRemark++;
            childList.emplace_back(reproduce(name.str()));
            retval++;
        }
    }
    return retval;
}

} // namespace Farm
