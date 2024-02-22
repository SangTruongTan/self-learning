#include "Animal.h"

namespace Farm {

Animal::Animal(std::string Name, SharedObjects &shared)
    : mName(Name), mAge(0), mWeight(0), mFeedConsecutiveDays(0),
      mShared(shared), mIsOutdoor(false), mNotGoOutdoorConsecutiveDays(0),
      mIsWentOutToday(false), mZeroHappyIndexConsecutiveDays(0),
      mHappyIndex(HAPPY_INDEX_DEFAULT), mChildrenRemark(CHILDREN_NAMING_NUMBER),
      mIntelligentIndex(INTELLIGENT_INDEX_DEFAULT) {
    std::stringstream ss{};
    ss << "New Animal named: " << mName;
    LOG_ANIMAL(LogLevel::DEBUG, ss.str());
    numOfSounds[AnimalType::CAT] = 0;
    numOfSounds[AnimalType::CHICKEN] = 0;
    numOfSounds[AnimalType::DOG] = 0;
    numOfSounds[AnimalType::PIG] = 0;
}

Animal::~Animal() { LOG_ANIMAL(LogLevel::DEBUG, "This animal will be dead"); }

const std::string Animal::getName(void) const { return this->mName; }

uint16_t Animal::getAge(void) const { return this->mAge; }

void Animal::incAge() {
    std::stringstream ss{};
    ss << "[" << this->mName << "] Inc Age to => " << ++this->mAge;
    LOG_ANIMAL(LogLevel::INFO, ss.str());
}

Animal::AnimalError Animal::feedAnimal(void) {
    AnimalError retval{AnimalNoError};
    retval = isEdible();
    if (retval == AnimalNoError) {
        std::stringstream ss{};
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
        {AnimalAgeNotAdequate, "AnimalAgeNotAdequate"},
        {AnimalIsOutdoor, "AnimalIsOutdoor"},
        {AnimalIsIndoor, "AnimalIsIndoor"},
        {AnimalAlreadyWentOutdoorToday, "AnimalAlreadyWentOutdoorToday"},
        {AnimalHappyIndexAlert, "AnimalHappyIndexAlert"}};

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
    if (mIsOutdoor == true) {
        numOfSounds.at(type) += num;
        LOG_ANIMAL(LogLevel::INFO, "[", mName, "] gain ", num, " sounds from ",
                   Animal::AnimalTypeToStrings.at(type), " => ",
                   numOfSounds.at(type));
    } else {
        LOG_ANIMAL(LogLevel::DEBUG, "[", mName, "] is outdoor");
    }
}

std::string Animal::getSoundStatusStrings(void) {
    std::stringstream ss{};
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
    std::stringstream name{};
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

Animal::AnimalError Animal::letAnimalGoOut(void) {
    Animal::AnimalError retval{AnimalNoError};
    if (mIsOutdoor == true) {
        LOG_ANIMAL(LogLevel::ERROR, "[", mName, "] already went outdoor");
        retval = Animal::AnimalError::AnimalIsOutdoor;
    } else if (mIsWentOutToday == true) {
        LOG_ANIMAL(LogLevel::ERROR, "[", mName, "] already went outdoor today");
        retval = Animal::AnimalError::AnimalAlreadyWentOutdoorToday;
    } else {
        LOG_ANIMAL(LogLevel::INFO, "let [", mName, "] went outdoor");
        mIsOutdoor = true;
        mNotGoOutdoorConsecutiveDays = 0;
        mIsWentOutToday = true;
        gainHappyIndex(GAIN_HAPPY_INDEX);
    }
    return retval;
}

Animal::AnimalError Animal::letAnimalGoBack(void) {
    Animal::AnimalError retval{AnimalNoError};
    if (mIsOutdoor == false) {
        LOG_ANIMAL(LogLevel::ERROR, "[", mName, "] is already indoor");
        retval = Animal::AnimalError::AnimalIsIndoor;
    } else {
        LOG_ANIMAL(LogLevel::INFO, "let [", mName, "] go back home");
        mIsOutdoor = false;
    }
    return retval;
}

bool Animal::getGoOutStatus(void) { return mIsOutdoor; }

// Define a function to convert AnimalType to string
std::string Animal::animalTypeToString(AnimalType type) {
    // Handle individual values
    auto it = AnimalTypeToStrings.find(type);
    if (it != AnimalTypeToStrings.end()) {
        return it->second;
    }

    // Check if the type is a combination of multiple values
    bool isChicken = (type & AnimalType::CHICKEN) == AnimalType::CHICKEN;
    bool isDog = (type & AnimalType::DOG) == AnimalType::DOG;
    bool isCat = (type & AnimalType::CAT) == AnimalType::CAT;
    bool isPig = (type & AnimalType::PIG) == AnimalType::PIG;
    if (isChicken || isDog || isCat || isPig) {
        LOG_ANIMAL(LogLevel::DEBUG, "MULTIPLE_ANIMALS <= ", isChicken, isDog,
                   isCat, isPig);
        return "MULTIPLE_ANIMALS";
    }
    // Handle unknown values
    return "UNKNOWN";
}

int Animal::gainHappyIndex(int offset) {
    LOG_ANIMAL(LogLevel::DEBUG, "Changed mHappyIndex (not aligned) from ",
               mHappyIndex, " to ", mHappyIndex + offset);
    int retval{-1};
    if (mType == AnimalType::PIG) {
        LOG_ANIMAL(LogLevel::DEBUG, "Pigs don't have the happy index");
    } else {
        mHappyIndex += offset;
        if (mHappyIndex < HAPPY_INDEX_MIN) {
            mHappyIndex = HAPPY_INDEX_MIN;
        } else if (mHappyIndex > HAPPY_INDEX_MAX) {
            mHappyIndex = HAPPY_INDEX_MAX;
            retval = mHappyIndex;
        }
    }

    return retval;
}

int Animal::getHappyIndex(void) {
    int retval = mHappyIndex;
    if (mType == AnimalType::PIG) {
        retval = HAPPY_INDEX_NOT_APPLICABLE;
    }
    return retval;
}

int Animal::getZeroHappyIndexConsecutiveDays(void) {
    return mZeroHappyIndexConsecutiveDays;
}

bool Animal::isDead(void) {
    return exceedLifeTime() |
           (mZeroHappyIndexConsecutiveDays >= DIE_WHEN_HAPPY_INDEX_ZERO);
}
} // namespace Farm
