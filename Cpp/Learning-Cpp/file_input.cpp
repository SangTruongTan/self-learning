#include <iostream>
#include <string>
#include <fstream>


int main() {
    std::ifstream file;
    std::string str;
    file.open("text_input.txt");
    if (file.fail()) {
        std::cout << "Open file failed" << std::endl;
    } else {
        while(!file.eof()) {
            std::getline(file, str);
            std::cout << str << std::endl;
        }
        file.close();
    }
    return(0);
}
