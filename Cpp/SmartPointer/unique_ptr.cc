#include <memory>
#include <iostream>

int main() {
    std::unique_ptr<int> ptr = std::make_unique<int>(42); // Preferred way to create
    std::cout << *ptr << std::endl; // Outputs 42
    // ptr goes out of scope here, memory is automatically freed
    return 0;
}
