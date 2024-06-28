/**
 * @file main.cpp
 * @author Sang Tan Truong (sang.truong@outlook.com.vn)
 * @brief Maximum Flow - Ford-Fulkerson
 * @link
 * https://www.hackerearth.com/practice/algorithms/graphs/maximum-flow/tutorial/
 * https://www.geeksforgeeks.org/ford-fulkerson-algorithm-for-maximum-flow-problem/
 * @version 0.1
 * @date 2024-06-28
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <climits>
#include <iostream>
#include <queue>
#include <vector>

#define V 6

bool bfs(int rGraph[V][V], int s, int t, int parent[]) {
    bool visited[V]{false};

    std::queue<int> q{};
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < V; v++) {
            if (visited[v] == false && rGraph[u][v] > 0) {
                parent[v] = u;
                if (v == t) return true;

                q.push(v);
                visited[v] = true;
            }
        }
    }

    return false;
}

int fordFulkerson(int graph[V][V], int s, int t) {
    int u, v;

    int rGraph[V][V];

    for (u = 0; u < V; u++) {
        for (v = 0; v < V; v++) {
            rGraph[u][v] = graph[u][v];
        }
    }
    int parent[V];

    int max_flow{0};

    while (bfs(rGraph, s, t, parent)) {
        int path_flow{INT_MAX};

        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            path_flow = std::min(path_flow, rGraph[u][v]);
        }

        // Update residual
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        max_flow += path_flow;
    }

    return max_flow;
}

int main() {

    // Graph
    int graph[V][V] = {{0, 16, 13, 0, 0, 0}, {0, 0, 10, 12, 0, 0},
                       {0, 4, 0, 0, 14, 0},  {0, 0, 9, 0, 0, 20},
                       {0, 0, 0, 7, 0, 4},   {0, 0, 0, 0, 0, 0}};

    std::cout << "The maximum possible flow is: " << fordFulkerson(graph, 0, 5)
              << std::endl;

    return EXIT_SUCCESS;
}
