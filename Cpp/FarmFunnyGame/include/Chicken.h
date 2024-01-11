#ifndef __CHICKEN_H__
#define __CHICKEN_H__

#include "Animal.h"

namespace Farm {
class Chicken : public Animal {
private:
public:
    Chicken(Farm::Logger *Log, std::string Name, Farm::SharedObjects &shared);
    ~Chicken();

    void incAge() override;
    void sound(int NumOfSound = 1) override;
    bool exceedLifeTime(void) override;
};
};

#endif /* __CHICKEN_H__ */
