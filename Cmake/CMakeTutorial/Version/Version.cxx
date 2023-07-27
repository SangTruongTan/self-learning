#include "Version.h"

#define STRING_INTERNAL(s) #s
#define STRING(s) STRING_INTERNAL(s)

std::string Version::Get() {
    static const std::string result {"v" STRING(__VERSION_MAJOR) "."
                                     STRING(__VERSION_MINOR) "."
                                     STRING(__VERSION_PATCH)};
    return result;
}
