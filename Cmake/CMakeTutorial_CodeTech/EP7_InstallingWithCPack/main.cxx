#include "ep7Config.h"
#ifdef USE_ADDER
#include "adder.h"
#endif
#include <iostream>

int main(int argc, const char **argv) {
    std::cout << argv[0] << " <== VERSION: " << EP7_VERSION_MAJOR << "."
              << EP7_VERSION_MINOR << "." << EP7_VERSION_PATCH << std::endl;
#ifdef USE_ADDER
    std::cout << "2 + 3 = " << mearlymath::add(2, 3) << std::endl;
#else
    std::cout << "Adder Library is disable" << std::endl;
#endif
    return EXIT_SUCCESS;
}
