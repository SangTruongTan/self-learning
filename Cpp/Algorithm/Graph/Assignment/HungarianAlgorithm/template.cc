//
//  main.cpp
//  Algorithm
//
//  Created by Sang Tan Truong on 28/5/24.
//

#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

void HungarianAlgorithm(const vector<vector<int>>& cost, vector<int>& assignment) {
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

int main() {
//    vector<vector<int>> cost = {
//        {4, 1, 3, 2},
//        {2, 0, 5, 3},
//        {3, 2, 2, 3},
//        {1, 4, 4, 2}
//    };
    vector<vector<int>> cost = {
        {1500, 4000, 4500},
        {2000, 6000, 3500},
        {2000, 4000, 2500}
    };
    int n = static_cast<int>(cost.size());
    vector<vector<int>> costMatrix(n + 1, vector<int>(n + 1, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            costMatrix[i + 1][j + 1] = cost[i][j];
        }
    }

    vector<int> assignment;
    HungarianAlgorithm(costMatrix, assignment);

    cout << "Optimal assignment:" << endl;
    for (int i = 0; i < assignment.size(); ++i) {
        cout << "Worker " << i + 1 << " assigned to job " << assignment[i] + 1 << endl;
    }

    return 0;
}
