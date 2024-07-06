/**
 * @file main.cpp
 * @author Sang Tan Truong (sang.truong@outlook.com.vn)
 * @brief Assignment Problem - Hungarian Algorithm
 * @link
 * https://www.hackerearth.com/practice/algorithms/graphs/minimum-cost-maximum-flow/tutorial/
 * @version 0.1
 * @date 2024-07-01
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <cassert>
#include <ctime>
#include <iostream>

#include <limits>
#include <vector>

using namespace std;

const int INF = numeric_limits<int>::max();

void HungarianAlgorithm(const vector<vector<int>>& cost,
                        vector<int>& assignment) {
    int n = static_cast<int>(cost.size());
    vector<int> u(n, 0), v(n, 0), p(n, 0), way(n, 0);

    for (int i = 1; i < n; ++i) {
        vector<int> minv(n, INF);
        vector<bool> used(n, false);
        int j0 = 0;
        p[0] = i;

        do {
            used[j0] = true;
            int i0 = p[j0], delta = INF, j1{0};
            for (int j = 1; j < n; ++j) {
                if (!used[j]) {
                    int cur = cost[i0][j] - u[i0] - v[j];
                    if (cur < minv[j]) {
                        minv[j] = cur;
                        way[j] = j0;
                    }
                    if (minv[j] < delta) {
                        delta = minv[j];
                        j1 = j;
                    }
                }
            }
            for (int j = 0; j < n; ++j) {
                if (used[j]) {
                    u[p[j]] += delta;
                    v[j] -= delta;
                } else {
                    minv[j] -= delta;
                }
            }
            j0 = j1;
        } while (p[j0] != 0);

        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);
    }

    assignment.resize(n - 1);
    for (int j = 1; j < n; ++j) {
        assignment[p[j] - 1] = j - 1;
    }
}

void ind() {}

void outd() {}

void solve() {
    int N;
    cin >> N;
    assert(N >= 1 && N <= 10);
    vector<vector<int>> costMatrix(N + 1, vector<int>(N + 1, 0));
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> costMatrix[i][j];
        }
    }

    vector<int> assignment;
    HungarianAlgorithm(costMatrix, assignment);

    int totalCost{0};
    for (int i = 0; i < assignment.size(); ++i) {
        totalCost += costMatrix[i + 1][assignment[i] + 1];
    }
    cout << totalCost << endl;
}

#ifdef TEST
int main1() {
#else
int main() {
#endif
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int T{1};
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
