/**
 * @file main.cpp
 * @author Sang Tan Truong (sang.truong@lge.com)
 * @brief Magic Donut Game
 * @link
 * https://codejam.lge.com/contest/problem/1383/2
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
#define MAX_M 123456
#define MOD 1000000007

int N, M;
int V[MAX_N + 1];
int S[MAX_M + 1];
int X[MAX_M + 1];
int Y[MAX_M + 1];

bool is_clockwise;
int origin{0};

void ind() {}

void outd() {}

int rotate(int orig, int step, bool is_clockwise) {
    if (is_clockwise) return  (origin + step) % N;
    else return (origin + N - step) % N;
}

void solve() {
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        cin >> V[i];
    }

    for (int i = 0; i < M; i++) {
        cin >> S[i];
    }

    for (int i = 0; i < M; i++) {
        cin >> X[i];
    }

    for (int i = 0; i < M; i++) {
        cin >> Y[i];
    }
    // Initialize
    is_clockwise = true;
    origin = 0;

    vector<int> O;
    // Each card
    for (int i = 0; i < M; i++) {
        if (S[i] == 1) {
            origin = rotate(origin, X[i], is_clockwise);
        } else if (S[i] == 2) {
            origin = rotate(origin, X[i], !is_clockwise);
        } else if (S[i] == 3) {
            is_clockwise = !is_clockwise;
        } else if (S[i] == 4) {
            int factor{((is_clockwise == true) ? 1 : -1)};
            for (int j = 0; j < X[i]; j++) {
                int index = (origin + j * factor + N) % N;
                V[index] += Y[i];
            }
        } else {
            int factor{((is_clockwise == true) ? 1 : -1)};
            int sum{0};
            // cout << "Y:" << Y[i] << endl;
            for (int j = 0; j < X[i]; j++) {
                int index = (origin + j * factor + N) % N;
                sum = (sum + V[index]) % MOD;
                // cout << "I'm here" <<endl;
            }
            O.push_back(sum);
        }
    }

    for (int i = 0; i < O.size(); i++) {
        cout << O[i] << " ";
    }
    cout << endl;
    
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
