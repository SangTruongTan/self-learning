/**
 * @file main.cpp
 * @author Sang Tan Truong (sang.truong@outlook.com.vn)
 * @brief Bellman-Ford Basic Implementation
 * @link
 * https://cp-algorithms.com/graph/bellman_ford.html
 * @version 0.1
 * @date 2024-06-25
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <iostream>
#include <utility>
#include <vector>

const int INF = 1000000000;

struct Edge {
    int a, b, cost;
};

void solve(int v, int t, int n, std::vector<Edge>& edges) {
    std::vector<int> d(n, INF);
    d[v] = 0;
    std::vector<int> p(n, -1);

    for (;;) {
        bool any{false};
        for (Edge e : edges) {
            if (d[e.a] < INF) {
                if (d[e.b] > d[e.a] + e.cost) {
                    d[e.b] = d[e.a] + e.cost;
                    p[e.b] = e.a;
                    any = true;
                }
            }
        }

        if (!any) {
            break;
        }
    }

    if (d[t] == INF) {
        std::cout << "No path from " << v << " to " << t << ".\n";
    } else {
        std::vector<int> path;
        for (int cur = t; cur != -1; cur = p[cur]) {
            path.push_back(cur);
        }

        std::cout << "Path from " << v << " to " << t << ": ";
        auto it{path.rbegin()};
        while (it != path.rend()) {
            std::cout << *it << ' ';
            std::advance(it, 1);
        }
        std::cout << std::endl;
    }
}

/*
1--->4
||\ /|\
|  \ |
v   \|
2 -->3

1-2: 1
2-3: 4
3-1: 2
3-4: 3
1-4: 1
*/
int main() {
    // Non-negative graph
    std::vector<Edge> edges = {
        {1, 2, 1}, {1, 4, 1}, {2, 3, 4}, {3, 1, 2}, {3, 4, 3}};
    int numberOfNodes{5};
    int start{1};
    int destination{4};
    solve(start, destination, numberOfNodes, edges);
    solve(4, 1, numberOfNodes, edges);
    return EXIT_SUCCESS;
}
