/**
 * @file main.cpp
 * @author Sang Tan Truong (sang.truong@outlook.com.vn)
 * @brief Maximum Flow - Dinic's Algorithm
 * @link
 * https://www.hackerearth.com/practice/algorithms/graphs/maximum-flow/tutorial/
 * https://www.geeksforgeeks.org/dinics-algorithm-maximum-flow/
 * @version 0.1
 * @date 2024-06-28
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <climits>
#include <iostream>
#include <list>
#include <vector>

struct Edge {
    // "To" vertex
    int v;

    // Current flow
    int flow;

    // Capacity
    int C;

    // Reverse edge index
    int rev;
};

class Graph {
    int V;
    int* level;
    std::vector<Edge>* adj;

public:
    Graph(int V) {
        adj = new std::vector<Edge>[V];
        this->V = V;
        level = new int[V];
    }
    ~Graph() {
        delete[] level;
        delete[] adj;
    }
    void addEdge(int u, int v, int C);
    bool BFS(int s, int t);
    int sendFlow(int s, int flow, int t, int ptr[]);
    int DinicMaxFlow(int s, int t);
};

void Graph::addEdge(int u, int v, int C) {
    // Forward edge: 0 flow and C capacity
    Edge a{v, 0, C, (int)adj[v].size()};

    // Back edge 0 flow and 0 capacity
    Edge b{u, 0, 0, (int)adj[u].size()};

    adj[u].push_back(a);
    adj[v].push_back(b); // Reverse edge
}

bool Graph::BFS(int s, int t) {
    for (int i = 0; i < V; i++) {
        level[i] = -1;
    }

    level[s] = 0;
    std::list<int> q;
    q.push_back(s);

    std::vector<Edge>::iterator i;
    while (!q.empty()) {
        int u = q.front();
        q.pop_front();

        for (i = adj[u].begin(); i != adj[u].end(); i++) {
            Edge& e = *i;
            if (level[e.v] < 0 && e.flow < e.C) {
                level[e.v] = level[u] + 1;
                q.push_back(e.v);
            }
        }
    }
    return level[t] > 0 ? true : false;
}

int Graph::sendFlow(int u, int flow, int t, int start[]) {
    if (u == t) return flow;

    // Traverse all adjacent edges one by one
    for (; start[u] < adj[u].size(); start[u]++) {
        Edge& e = adj[u][start[u]];

        if (level[e.v] == level[u] + 1 && e.flow < e.C) {
            int curr_flow = std::min(flow, e.C - e.flow);

            int temp_flow = sendFlow(e.v, curr_flow, t, start);

            if (temp_flow > 0) {
                e.flow += temp_flow;

                // Substract fwlo from reverse edge of current edge
                adj[e.v][e.rev].flow -= temp_flow;
                return temp_flow;
            }
        }
    }
    return 0;
}

int Graph::DinicMaxFlow(int s, int t) {
    // Coner case
    if (s == t) return -1;

    int total = 0;

    // Aument the flow while there is path from source to sink
    while (BFS(s, t) == true) {
        int* start = new int[V + 1]{0};

        while (int flow = sendFlow(s, INT_MAX, t, start)) {
            total += flow;
        }

        delete[] start;
    }

    return total;
}

int main() {
    Graph g(6);
    g.addEdge(0, 1, 16);
    g.addEdge(0, 2, 13);
    g.addEdge(1, 2, 10);
    g.addEdge(1, 3, 12);
    g.addEdge(2, 1, 4);
    g.addEdge(2, 4, 14);
    g.addEdge(3, 2, 9);
    g.addEdge(3, 5, 20);
    g.addEdge(4, 3, 7);
    g.addEdge(4, 5, 4);

    std::cout << "Maximum flow: " << g.DinicMaxFlow(0, 5) << std::endl;

    return EXIT_SUCCESS;
}
