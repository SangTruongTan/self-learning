#include "ep6Config.h"
#ifdef USE_ADDER
#include "adder.h"
#endif
#include <iostream>


int main() {
#ifdef USE_ADDER
    std::cout << "2 + 3 = " << mearlymath::add(2, 3) << std::endl;
#else
    std::cout << "Adder Library is disable" << std::endl;
#endif
    return EXIT_SUCCESS;
}
