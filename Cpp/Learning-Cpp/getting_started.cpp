#include <iostream>
#include <string>

int main() {
    std::string name;
    std::cout << "What's your name:";
    std::cin >> name;
    std::cout << std::endl << "My name is:" << name << std::endl;
    return(0);
}