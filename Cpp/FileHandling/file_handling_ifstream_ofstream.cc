#include <fstream>
#include <iostream>

int main() {
    std::ofstream fout;

    std::string line;

    fout.open("sample.txt");

    std::cout << "Type your text (terminal by \"1\"):" << std::endl;

    while (fout) {
        std::getline(std::cin, line);

        if (line == "1") break;

        fout << line << std::endl;
    }
    fout.close();

    std::ifstream fin;

    fin.open("sample.txt");

    std::cout << "Content from the file:" << std::endl;

    while (std::getline(fin, line)) {
        std::cout << line << std::endl;
    }

    fin.close();

    return EXIT_SUCCESS;
}
