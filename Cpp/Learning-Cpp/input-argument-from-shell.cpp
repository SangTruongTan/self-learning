#include <iostream>

int main(int argc, char *argv[]) {
    std::cout << "Number of arguments:" << argc << std::endl;
    for (int i = 0; i < argc; i++) {
        // printf("Argument:[%d] => %s\r\n", i, argv[i]);
        std::cout << "Argument:[" + std::to_string(i) + std::string("] => ") + argv[i]
                  << std::endl;
    }
}

/*
Input: ./a.out arg1 arg2 arg3
Output:
Number of arguments:4
Argument:[0] => ./a.out
Argument:[1] => arg1
Argument:[2] => arg2
Argument:[3] => arg3
*/
