/**
 ******************************************************************************
 * @file           : Cat.h
 * @brief          : Cat's header file.
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
#ifndef __CAT_H__
#define __CAT_H__

/* Includes ------------------------------------------------------------------*/
#include "Animal.h"

/* Declarations --------------------------------------------------------------*/
namespace Farm {
class Cat : public Animal {
private:
    AnimalError isEdible(void) override;

public:
    Cat(std::string Name, Farm::SharedObjects &shared);
    ~Cat();
    void sound(int NumOfSound = 1) override;
    bool exceedLifeTime(void) override;
    void scanAnimal(void) override;
    bool isSalable(void) const override;
    void killAnimal(void) override;
    int getSellPrice(void) const override;
    AnimalType getType(void) const override;
    int checkHappyReductionBySounds(void) override;
    bool isReproducible(void) override;
    Animal *reproduce(std::string name) const override;
    int getNumberOfChilds(void) override;
    void soundWhenBorn(void) override;
    int gainIntelligentIndex(int offset) override;
    int getIntelligentIndex(void) const override;
    AnimalError trainAnimal(void) override;
};
}; // namespace Farm

#endif /* __CAT_H__ */
