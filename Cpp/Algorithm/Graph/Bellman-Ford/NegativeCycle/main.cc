/**
 * @file main.cpp
 * @author Sang Tan Truong (sang.truong@outlook.com.vn)
 * @brief Bellman-Ford Negative Cycle
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

void solve(int v, int n, std::vector<Edge>& edges) {
    std::vector<int> d(n, INF);
    d[v] = 0;
    std::vector<int> p(n, -1);
    int x;
    // Bellman-Ford algorithm only needs n - 1 phase for non-negative graph.
    // If it exceeds n - 1 phase means existing at least a negative cycle.
    for (int i = 0; i < n; i++) {
        x = -1;
        for (Edge e : edges) {
            if (d[e.a] < INF) {
                if (d[e.b] > d[e.a] + e.cost) {
                    // Limit the distance to -INF (distance might reach -nmW)
                    d[e.b] = std::max(-INF, d[e.a] + e.cost);
                    p[e.b] = e.a;
                    x = e.b;
                }
            }
        }
    }

    if (x == -1) {
        std::cout << "No negative cycle from " << v << std::endl;
    } else {
        int y = x;
        for (int i = 0; i < n; i++) {
            y = p[y];
        }

        std::vector<int> path;
        for (int cur = y;; cur = p[cur]) {
            path.push_back(cur);
            if (cur == y && path.size() > 1) {
                break;
            }
        }

        std::cout << "Negative cycle: ";
        auto it{path.rbegin()};
        while (it != path.rend()) {
            std::cout << *it << ' ';
            std::advance(it, 1);
        }
        std::cout << std::endl;
    }
}

/*
edges1:

1--->4
||\ /|\
|  \ |
v   \|
2 -->3

1-2: 1
2-3:-4
3-1: 2
3-4: 3
1-4: 1

edges2:

1--->4
|   /|\
|    |
v    |
2 -->3

1-2: 1
2-3:-4
3-4: 3
1-4: 1

edges3:

1<---4
||\ /|\
|  5 |
v  |\|
2 -->3

1-2: 1
4-1: 1
2-3:-4
3-4:-3
3-5:1
5-1:1
*/
int main() {
    // Non-negative graph
    std::vector<Edge> edges1 = {
        {1, 2, 1}, {1, 4, 1}, {2, 3, -4}, {3, 1, 2}, {3, 4, 3}};
    int numberOfNodes{5};
    int start{1};
    solve(start, numberOfNodes, edges1);

    std::vector<Edge> edges2 = {{1, 2, 1}, {1, 4, 1}, {2, 3, -4}, {3, 4, 3}};

    solve(start, numberOfNodes, edges2);

    // In the presence of a negative cycle(s), there are further complications
    // associated with the fact that distances to all vertices in this cycle, as
    // well as the distances to the vertices reachable from this cycle is not
    // defined — they should be equal to minus infinity (-oo).
    std::vector<Edge> edges3 = {{1, 2, 1},  {4, 1, 1}, {2, 3, -4},
                                {3, 4, -3}, {3, 5, 1}, {5, 1, 1}};

    solve(start, 6, edges3);
    // As a result, the node 5 is listed in the negative cycle but it is
    // reachable from the negative cycle.
    return EXIT_SUCCESS;
}
