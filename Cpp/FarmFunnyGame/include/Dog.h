#ifndef __DOG_H__
#define __DOG_H__

#include "Animal.h"

namespace Farm {
class Dog : public Animal {
private:
    AnimalError isEdible(void) override;

public:
    Dog(std::string Name, Farm::SharedObjects &shared);
    ~Dog();
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

#endif /* __DOG_H__ */
