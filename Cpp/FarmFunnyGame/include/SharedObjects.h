#ifndef __SHARED_OBJECTS_H__
#define __SHARED_OBJECTS_H__

#include <functional>

namespace Farm {
/* Enum definiton. */
enum AnimalType { CHICKEN, CAT, PIG, DOG, ANIMAL, SPECIFIC_ANIMAL };
struct SharedObjects {
    std::function<void(AnimalType, int)> soundCallback;
};

}; // namespace Farm
#endif
