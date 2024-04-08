/**
 ******************************************************************************
 * @file           : Animal_mock.hpp
 * @brief          : Animal's mock file.
 ******************************************************************************
 * @attention
 *
 * BSD 3-Clause License
 *
 * Copyright (c) 2024, Sang Tan Truong.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of Sang Tan Truong nor the names of its contributors may
 *    be used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ANIMAL_MOCK_H__
#define __ANIMAL_MOCK_H__

/* Includes ------------------------------------------------------------------*/

/* Mock class defintions -----------------------------------------------------*/
class AnimalMock {
public:
    MOCK_METHOD0(getName, std::string());
    MOCK_METHOD0(getAge, uint16_t());
    MOCK_METHOD0(incAge, void());
    MOCK_METHOD0(feedAnimal, Farm::Animal::AnimalError());
    MOCK_METHOD0(getWeight, double());
    MOCK_METHOD0(getFeedConsecutiveDays, int());
    MOCK_METHOD0(getFedToday, bool());
    MOCK_METHOD0(clearSound, void());
    MOCK_METHOD2(gainSound, void(Farm::AnimalType type, int num));
    MOCK_METHOD0(getSoundStatusStrings, std::string());
    MOCK_METHOD1(reproduce, int(Farm::Animal::AnimalList &childList));
    MOCK_METHOD0(letAnimalGoOut, Farm::Animal::AnimalError());
    MOCK_METHOD0(letAnimalGoBack, Farm::Animal::AnimalError());
    MOCK_METHOD0(getGoOutStatus, bool());
    MOCK_METHOD1(animalTypeToString, std::string(Farm::AnimalType type));
    MOCK_METHOD1(gainHappyIndex, int(int offset));
    MOCK_METHOD0(getHappyIndex, int());
    MOCK_METHOD0(getZeroHappyIndexConsecutiveDays, int());
    MOCK_METHOD0(isDead, bool());
};

/* Define Mock Object --------------------------------------------------------*/

AnimalMock *M_Animal{nullptr};

/* Mock Target defintions ----------------------------------------------------*/
Farm::Animal::Animal(std::string Name, SharedObjects &shared)
    : mName(Name), mAge(0), mWeight(0), mFeedConsecutiveDays(0),
      mShared(shared), mIsOutdoor(false), mNotGoOutdoorConsecutiveDays(0),
      mIsWentOutToday(false), mZeroHappyIndexConsecutiveDays(0),
      mHappyIndex(HAPPY_INDEX_DEFAULT), mChildrenRemark(CHILDREN_NAMING_NUMBER),
      mIntelligentIndex(INTELLIGENT_INDEX_DEFAULT), isTrainedToday(false) {}

Farm::Animal::~Animal() {}

const std::string Farm::Animal::getName(void) const {
    return M_Animal->getName();
}

uint16_t Farm::Animal::getAge(void) const { return M_Animal->getAge(); }

void Farm::Animal::incAge(void) { return M_Animal->incAge(); }

Farm::Animal::AnimalError Farm::Animal::feedAnimal(void) {
    return M_Animal->feedAnimal();
}

double Farm::Animal::getWeight(void) { return M_Animal->getWeight(); }

int Farm::Animal::getFeedConsecutiveDays(void) {
    return M_Animal->getFeedConsecutiveDays();
}

bool Farm::Animal::getFedToday(void) { return M_Animal->getFedToday(); }

void Farm::Animal::clearSound(void) { return M_Animal->clearSound(); }

void Farm::Animal::gainSound(AnimalType type, int num) {
    return M_Animal->gainSound(type, num);
}

std::string Farm::Animal::getSoundStatusStrings(void) {
    return M_Animal->getSoundStatusStrings();
}

int Farm::Animal::reproduce(AnimalList &childList) {
    return M_Animal->reproduce(childList);
}

Farm::Animal::AnimalError Farm::Animal::letAnimalGoOut(void) {
    return M_Animal->letAnimalGoOut();
}

Farm::Animal::AnimalError Farm::Animal::letAnimalGoBack(void) {
    return M_Animal->letAnimalGoBack();
}

bool Farm::Animal::getGoOutStatus(void) { return M_Animal->getGoOutStatus(); }

std::string Farm::Animal::animalTypeToString(AnimalType type) {
    return M_Animal->animalTypeToString(type);
}

int Farm::Animal::gainHappyIndex(int offset) {
    return M_Animal->gainHappyIndex(offset);
}

int Farm::Animal::getHappyIndex(void) { return M_Animal->getHappyIndex(); }

int Farm::Animal::getZeroHappyIndexConsecutiveDays(void) {
    return M_Animal->getZeroHappyIndexConsecutiveDays();
}

bool Farm::Animal::isDead(void) { return M_Animal->isDead(); }

#endif /* __ANIMAL_MOCK_H__ */