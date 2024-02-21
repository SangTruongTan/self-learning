#ifndef __CAT_H__
#define __CAT_H__

#include "Animal.h"

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
};
}; // namespace Farm

#endif /* __CAT_H__ */
