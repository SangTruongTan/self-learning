#include <fstream>
#include <iostream>

int main() {
    std::fstream fio;

    std::string line;

    // by default openmode = std::ios::in|std::ios::out mode
    // Automatically overwrites the content of file, To append
    // the content, open in std::ios::app
    // fio.open("sample.txt", std::ios::in||std::ios::out||std::ios::app)
    // std::ios::trunc mode delete all content before open
    fio.open("sample.txt", std::ios::trunc | std::ios::out | std::ios::in);

    std::cout << "Type your text (terminal by \"-1\"):" << std::endl;

    while (fio) {
        std::getline(std::cin, line);

        if (line == "-1") break;

        fio << line << std::endl;
    }

    // Execute a loop until EOF (End of File)
    // point read pointer at beginning of file
    fio.seekg(0, std::ios::beg);
    std::cout << "Content from the file:" << std::endl;

    while (fio) {
        std::getline(fio, line);

        std::cout << line << std::endl;
    }

    fio.close();

    return EXIT_SUCCESS;
}
