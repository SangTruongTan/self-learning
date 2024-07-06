/**
 * @file main.cpp
 * @author Sang Tan Truong (sang.truong@outlook.com.vn)
 * @brief OrOasis
 * @link
 * https://www.hackerearth.com/practice/algorithms/greedy/basics-of-greedy-algorithms/practice-problems/algorithm/oroasis-7e736f17/
 * @version 0.1
 * @date 2024-05-02
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <cassert>
#include <ctime>
#include <iostream>
#include <map>
#include <vector>
// #include <bits/stdc++.h>

#define TEST

int32_t totalN;

void ind() {}

void outd() {}

void solve() {
    int32_t N;
    std::cin >> N;
    assert(N >= 2 && N <= 1e6);
    totalN += N;
    std::vector<int32_t> arr(N);
    for (auto &element : arr) {
        std::cin >> element;
        assert(element >= 0 && element <= 1e9);
    }

    std::vector<std::vector<int32_t>> bitSum(30, std::vector<int32_t>(N));

    for (int i = 0; i < N; i++) {
        for (int bit = 0; bit < 30; bit++) {
            bitSum[bit][i] = ((arr[i] & (1 << bit)) > 0);
            if (i != 0) {
                bitSum[bit][i] += bitSum[bit][i - 1];
            }
        }
    }

    auto getSum = [&](int bit, int l, int r) {
        if (l == 0) return bitSum[bit][r];
        return bitSum[bit][r] - bitSum[bit][l - 1];
    };

    auto check = [&](int l, int r) {
        for (int bit = 0; bit < 30; bit++) {
            if (bitSum[bit][N - 1] > 0 && getSum(bit, l, r) == 0) return false;
        }
        return true;
    };

    auto check2 = [&](int l, int r) {
        for (int bit = 0; bit < 30; bit++) {
            if (bitSum[bit][N - 1] > 0 &&
                getSum(bit, l, r) == bitSum[bit][N - 1])
                return false;
        }
        return true;
    };

    std::vector<int> min(N + 1);
    int minLength{N + 1};

    for (int i = 0, j = 0; i < N; i++) {
        while (j < i && check(j + 1, i))
            j++;
        if (check(j, i) && check2(j, i)) {
            minLength = std::min(minLength, i - j + 1);
            // std::cout << i << "|" << j << "|" << minLength << std::endl;
            min[i - j + 1] += 1;
        }
    }
    if (minLength == N + 1) {
        std::cout << -1 << std::endl;
    } else {
        std::cout << minLength << " " << min[minLength] << std::endl;
    }
}

#ifdef TEST
int main1() {
#else
int main() {
#endif
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int T;
    std::cin >> T;
    assert(T >= 1 && T <= 1e5);
    totalN = 0;
    while (T--) {
        ind();
        solve();
        outd();
    }
    assert(totalN <= 1e6);
    return 0;
}

#ifdef TEST
int main() {
    ::freopen("input.txt", "r", stdin);
    ::freopen("output.txt", "w", stdout);
    ::clock_t tStart = ::clock();
    main1();
    std::cout << std::endl;
    ::printf("Time taken: %.10fs\n",
             (double)(::clock() - tStart) / CLOCKS_PER_SEC);
    ::fclose(stdin);
    ::fclose(stdout);
    return EXIT_SUCCESS;
}
#endif
