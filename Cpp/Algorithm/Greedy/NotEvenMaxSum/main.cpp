/**
 * @file main.cpp
 * @author Sang Tan Truong (sang.truong@outlook.com.vn)
 * @brief Not Even Max Sum
 * @link
 * https://www.hackerearth.com/practice/algorithms/greedy/basics-of-greedy-algorithms/practice-problems/algorithm/not-even-max-sum-a3ccf284/
 * @version 0.1
 * @date 2024-05-03
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <algorithm>
#include <ctime>
#include <iostream>
#include <map>
// #include <bits/stdc++.h>

#define TEST

int N;
int A[100000 + 10];
long long TotalSum;
long long result;
int minOdd;

void ind() {}

void outd() {}

void solve() {
    TotalSum = 0;
    std::cin >> N;
    minOdd = __INT_MAX__;
    for (int i = 0; i < N; i++) {
        std::cin >> A[i];
        TotalSum += A[i];
        if (A[i] % 2 != 0 && minOdd > A[i]) {
            minOdd = A[i];
        }
    }

    if (TotalSum % 2 != 0) {
        result = TotalSum;
    } else {
        if (minOdd == __INT_MAX__) {
            result = 0;
        } else {
            result = TotalSum - minOdd;
        }
    }
    std::cout << result << std::endl;
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
    while (T--) {
        ind();
        solve();
        outd();
    }
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
