#include <iostream>
using namespace std;

// Enter your code for reversed_binary_value<bool...>()
int convert(int Result, int pos) { return Result; }
template <typename T, typename... Targs>
int convert(int Result, int pos, T Value = 0, Targs... FArgs) {
    int val = Value == true ? 0x0000000000000001 : 0x0000000000000000;
    int Res = Result | (val << pos);
    int newpos = pos + 1;
    return convert(Res, newpos, FArgs...);
}
template <bool... Args> int reversed_binary_value() {
    int retVal = convert(0, 0, Args...);
    return retVal;
}

template <int n, bool... digits> struct CheckValues {
    static void check(int x, int y) {
        CheckValues<n - 1, 0, digits...>::check(x, y);
        CheckValues<n - 1, 1, digits...>::check(x, y);
    }
};

template <bool... digits> struct CheckValues<0, digits...> {
    static void check(int x, int y) {
        int z = reversed_binary_value<digits...>();
        std::cout << (z + 64 * y == x);
    }
};

int main() {
    int t;
    std::cin >> t;

    for (int i = 0; i != t; ++i) {
        int x, y;
        cin >> x >> y;
        CheckValues<6>::check(x, y);
        cout << "\n";
    }
}
