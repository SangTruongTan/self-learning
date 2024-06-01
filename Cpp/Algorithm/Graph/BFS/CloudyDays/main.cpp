/**
 * @file main.cpp
 * @author Sang Tan Truong (sang.truong@outlook.com.vn)
 * @brief Cloudy Days
 * @link
 * https://www.hackerearth.com/practice/algorithms/graphs/breadth-first-search/practice-problems/algorithm/cloudy-days-82a872ec/
 * @version 0.1
 * @date 2024-06-01
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <cassert>
#include <ctime>
#include <iostream>

#include <queue>
#include <utility>
#include <vector>
// #include <bits/stdc++.h>

// #define TEST

void ind() {}

void outd() {}

void solve() {
    int N, M, K, C;
    int u, v;
    std::cin >> N >> M >> K >> C;

    assert(N >= 2 && N <= 1e3);
    assert(M >= 0 && M <= (N * (N - 1)) >> 1);
    assert(K >= 1 && K <= 1e6);
    assert(C >= 1 && C <= N);

    std::vector<std::vector<int>> adj(N + 1);

    while (M-- > 0) {
        std::cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    std::queue<std::pair<int, int>> q{};
    std::vector<bool> visited(N + 1, false);
    q.push(std::make_pair(C, K));
    visited[C] = true;
    int numOfCities{1};

    while (!q.empty()) {
        auto [city, currentFuel] = q.front();
        q.pop();

        if (currentFuel > 0) {
            for (int nextCity : adj[city]) {
                if (!visited[nextCity]) {
                    q.push(std::make_pair(nextCity, currentFuel - 1));
                    visited[nextCity] = true;
                    numOfCities += 1;
                }
            }
        }
    }
    std::cout << numOfCities << std::endl;
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
