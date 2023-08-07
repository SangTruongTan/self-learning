#include <iostream>
#include "ep4Config.h"

int main(int agc, char * argv[]) {
    std::cout << argv[0] << " >> Version: " << EP4_VERSION_MAJOR << "."
              << EP4_VERSION_MINOR << "." << EP4_VERSION_PATCH << std::endl;
}
