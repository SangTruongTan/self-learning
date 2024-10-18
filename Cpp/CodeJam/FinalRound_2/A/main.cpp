/**
 * @file main.cpp
 * @author Sang Tan Truong (sang.truong@lge.com)
 * @brief Random Best-of Series
 * @link
 * https://codejam.lge.com/contest/problem/1383/1
 * @version 0.1
 * @date 2024-10-17
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <cassert>
#include <ctime>
#include <iostream>

#include <algorithm>
#include <climits>
#include <cmath>
#include <queue>
#include <utility>
#include <vector>
// #include <bits/stdc++.h>

// #define TEST

using namespace std;

#define MAX_N 250000

int N, M;

bool W[MAX_N + 1] = {false}; // false == A | true == B

int countMap[MAX_N + 1]; // Count B

void ind() {}

void outd() {}

// Return A:B
// 0-index
vector<int> count(int start, int end) {
    int numB;
    // Consider B
    numB = countMap[end % N] - countMap[start] + (W[start] == true);
    if (end >= N) numB += countMap[N - 1];
    return {end - start + 1 - numB, numB};
}

void solve() {

    cin >> N >> M;
    // cout << "N: " << N << ", M: " << M << endl;
    for (int i = 0; i < N; i++) {
        char temp;
        cin >> temp;
        W[i] = (temp == 'B');
        // cout << "W[" << i << "] = " << W[i] << endl;
    }

    long long sum{0};
    // Start from index 0
    // Construct count map
    countMap[0] = (W[0] == true);
    for (int i = 1; i < N; i++) {
        countMap[i] = countMap[i - 1] + (W[i] == true);
    }
    for (int j = 0; j < M; j++) {
        int sj, gj;
        cin >> sj >> gj;
        int low{(gj + 1) / 2};
        int high{gj};
        int mid;
        int min{INT_MAX};
        while (low <= high) {
            mid = (high + low) / 2;
            vector<int> temp = count(sj - 1, sj + mid - 1 - 1);
            // cout << "Temp[0] " << temp[0] << "Temp[1] " << temp[1] << endl;
            if (temp[0] * 2 >= gj || temp[1] * 2 >= gj) {
                if (min > mid) {
                    min = mid;
                }

                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        sum += min;
        // cout << min << endl;
    }
    cout << sum << endl;
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
