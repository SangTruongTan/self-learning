#ifndef __CHICKEN_H__
#define __CHICKEN_H__

#include "Animal.h"

namespace Farm {
class Chicken : public Animal {
private:
public:
    Chicken(std::string Name, Farm::SharedObjects &shared);
    ~Chicken();
    void sound(int NumOfSound = 1) override;
    bool exceedLifeTime(void) override;
    void scanAnimal(void) override;
};
}; // namespace Farm

#endif /* __CHICKEN_H__ */
