/**
 * @file scope.cxx
 * @author Sang Tan Truong (sang.truong@outlook.com.vn)
 * @brief Scope operator
 * @version 0.1
 * @date 2024-05-07
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <iostream>

int i = 89;

namespace {
int i = 98; // inaccessible, ambiguous i
}

int main() {
    int i = 0; // local i overloads global i

    std::cout << i << std::endl;   // local
    std::cout << ::i << std::endl; // global

    return EXIT_SUCCESS;
}
