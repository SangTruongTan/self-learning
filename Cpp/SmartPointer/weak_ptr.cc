#include <memory>
#include <iostream>

int main() {
    std::shared_ptr<int> sp = std::make_shared<int>(42);
    std::weak_ptr<int> wp = sp; // wp is a weak reference to the same int

    std::cout << "Shared_ptr use count: " << sp.use_count() << std::endl; // Outputs 1 (wp doesn't increment it)

    // Access the object via weak_ptr
    if (auto temp = wp.lock()) { // Try to get a shared_ptr
        std::cout << "Value: " << *temp << std::endl; // Outputs 42
        std::cout << "Shared_ptr use count: " << sp.use_count() << std::endl; // Outputs 1 (wp doesn't increment it)
    } else {
        std::cout << "Object is gone" << std::endl;
    }

    sp.reset(); // Deletes the object, wp becomes expired

    if (auto temp = wp.lock()) {
        std::cout << "Value: " << *temp << std::endl;
    } else {
        std::cout << "Object is gone" << std::endl; // Outputs this
    }

    return 0;
}
