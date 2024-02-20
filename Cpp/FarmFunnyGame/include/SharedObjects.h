#ifndef __SHARED_OBJECTS_H__
#define __SHARED_OBJECTS_H__

#include <functional>

namespace Farm {
/* Enum definiton. */
enum AnimalType {
    CHICKEN = 0x01,
    CAT = 0x02,
    PIG = 0x04,
    DOG = 0x08,
    ANIMAL = 0x10,
    SPECIFIC_ANIMAL = 0x20
};
struct SharedObjects {
    std::function<void(AnimalType, int)> soundCallback;
};

}; // namespace Farm
#endif
