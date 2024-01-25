#include <iostream>
#include <vector>
#include <iterator>
#include <unordered_map>

int main() {
    std::unordered_map<int, std::string> mp = {{1, "1"}, {2, "2"}};

    std::cout << mp.at(3);

    return 0;
}