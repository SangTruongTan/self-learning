/**
 * @file main.cpp
 * @author Sang Tan Truong (sang.truong@outlook.com.vn)
 * @brief Addition Game with Digit Cards
 * @link
 * https://codejam.lge.com/contest/problem/1251/1
 * @version 0.1
 * @date 2024-08-09
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <cassert>
#include <ctime>
#include <iostream>

#include <algorithm>
#include <cmath>
#include <queue>
#include <utility>
#include <vector>
// #include <bits/stdc++.h>

// #define TEST

using namespace std;

void ind() {}

void outd() {}

void solve() {
    int N;
    int X[15];
    int M{0};
    std::cin >> N;
    std::string strX;
    std::cin >> strX;
    M = strX.length();
    for (int i = 0; i < M; i++) {
        X[i] = strX[i] - '0';
    }
    // Build matrix
    long long matrix[15][15];
    for (int i = 0; i < M; i++) {
        long long temp{0};
        for (int j = i; j < M; j++) {
            temp = temp * 10 + X[j];
            matrix[i][j] = temp;
        }
    }

    // Build map
    int row = pow(2, M - 1);
    int start[16384] = {0};
    vector<pair<long long, int>> vec(row);
    int reverse{row};
    for (int i = 0; i < M - 1; i++) {
        reverse /= 2;
        int cnt{0};
        for (int j = 0; j < row; j++) {
            // Check
            vec[j].first += matrix[start[j]][i];
            start[j] = i + 1;
            vec[j].second += 1;
            if (++cnt == reverse) {
                cnt = 0;
                j += reverse;
                continue;
            }

        }
    }

    for (int j = 0; j < row; j++) {
        vec[j].first += matrix[start[j]][M - 1];
        // if (start[j] == M - 1) vec[j].second += 1;
    }

    stable_sort(vec.begin(), vec.end(),
                [](pair<long long, int> lhs, pair<long long, int> rhs) {
                    return lhs.first < rhs.first;
                });
    // cout << "Begin:\n";
    // for (int i = 0; i < row; i++) {
    //     cout << vec[i].first << " " << vec[i].second << endl;
    // }
    // cout << "End:\n";
    // Read and write answer
    long long Ws{0};
    int Wp{0};
    int temp;
    for (int i = 0; i < N; i++) {
        std::cin >> temp;
        temp -= 1;
        Ws += vec[temp].first;
        Wp += vec[temp].second;
    }
    std::cout << Ws << " " << Wp << std::endl;
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
