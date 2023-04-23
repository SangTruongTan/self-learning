#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    unsigned int N, S, P, Q;
    std::cin >> N >> S >> P >> Q;
    unsigned int mod = pow(2, 31);
    unsigned int prev;
    unsigned int curr;
    int count = 1;
    prev = S % mod;
    for (int i = 1; i < N; i++) {
        unsigned int curr = (prev * P + Q) % mod;
        count += curr != prev ? 1 : 0;
        prev = curr;
    }
    std::cout << count;
    return 0;
}
