#include <iostream>
#include <fstream>

int main() {
    std::ofstream file;
    file.open("file_output.txt");
    if (file.fail()) {
        std::cout << "Failed to open file" << std::endl;
    } else {
        file << "Hell World!" << std::endl;
        file << "My name is Sang" << std::endl;
        file << "I'm working for LGE" << std::endl;
        file.close();
    }
    return(0);
}
