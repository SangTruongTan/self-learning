#include <memory>
#include <iostream>

int main() {
    std::shared_ptr<int> ptr1 = std::make_shared<int>(100); // Preferred way to create
    {
        std::shared_ptr<int> ptr2 = ptr1; // Reference count = 2
        std::cout << *ptr2 << std::endl; // Outputs 100
        std::cout << "Count: " << ptr1.use_count() << " " << ptr2.use_count() << std::endl;
    } // ptr2 goes out of scope, reference count drops to 1
    std::cout << *ptr1 << std::endl; // Still valid, outputs 100
    std::cout << "Count: " << ptr1.use_count() << std::endl;
    // ptr1 goes out of scope, reference count = 0, memory freed
    return 0;
}
