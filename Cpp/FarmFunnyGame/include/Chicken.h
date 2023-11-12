#ifndef __CHICKEN_H__
#define __CHICKEN_H__

#include "Animal.h"

namespace Farm {
class Chicken : public Animal {
private:
public:
    Chicken(Farm::Logger *Log, const char *Name, Farm::SharedObjects &shared);
    ~Chicken();
    const char *getName(void) override;
    uint16_t getAge(void) override;
    void incAge() override;
    void sound(int NumOfSound = 1) override;
    bool exceedLifeTime(void) override;
};
};

#endif /* __CHICKEN_H__ */
