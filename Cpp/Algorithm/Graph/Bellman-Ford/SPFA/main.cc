/**
 * @file main.cpp
 * @author Sang Tan Truong (sang.truong@outlook.com.vn)
 * @brief Bellman-Ford Shortest Path Faster Algorithm (SPFA)
 * @link
 * https://cp-algorithms.com/graph/bellman_ford.html
 * @version 0.1
 * @date 2024-06-26
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>

const int INF = 1000000000;
std::vector<std::vector<std::pair<int, int>>> adj;

bool spfa(int s, std::vector<int>& d) {
    int n = adj.size();
    d.assign(n, INF);
    std::vector<int> cnt(n, 0);
    std::vector<bool> inqueue(n, false);
    std::queue<int> q{};

    d[s] = 0;
    q.push(s);
    inqueue[s] = true;
    while (!q.empty()) {
        int v = q.front();
        q.pop();

        inqueue[v] = false;

        for (auto edge : adj[v]) {
            int to = edge.first;
            int len = edge.second;

            if (d[to] > d[v] + len) {
                d[to] = d[v] + len;
                if (!inqueue[to]) {
                    q.push(to);
                    inqueue[to] = true;
                    cnt[to] += 1;
                    if (cnt[to] > n) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

/*
edges1:

1--->0
||\ /|\
|  \ |
v   \|
2 -->3

1-2: 1
2-3:-4
3-1: 2
3-0: 3
1-0: 1

edges2:

1--->0
|   /|\
|    |
v    |
2 -->3

1-2: 1
2-3:-4
3-0: 3
1-0: 1

*/
int main() {
    // Non-negative graph
    adj = {{{0, 0}}, {{0, 1}, {2, 1}}, {{3, 4}}, {{0, 3}, {1, 2}}};
    std::vector<int> d(4);
    bool result = spfa(1, d);
    std::string resTrue{"Do not contain any negative cycle"};
    std::string resFalse{"Includes a negative cycle"};
    std::cout << "Non-negative graph check...\n";
    std::cout << (result ? resTrue : resFalse) << std::endl << std::endl;

    // Includes a negative cycle
    adj = {{{0, 0}}, {{0, 1}, {2, 1}}, {{3, -4}}, {{0, 3}, {1, 2}}};
    result = spfa(1, d);
    std::cout << "Negative graph check...\n";
    std::cout << (result ? resTrue : resFalse) << std::endl;
    return EXIT_SUCCESS;
}