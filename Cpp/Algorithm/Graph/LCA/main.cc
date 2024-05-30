/**
 * @file main.cc
 * @author Sang Tan Truong (sang.truong@outlook.com.vn)
 * @brief LCA - Lowest Common Ancestor with Segment Tree
 * @link
 * https://cp-algorithms.com/graph/lca.html
 * @version 0.1
 * @date 2024-05-30
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <cassert>
#include <iostream>

#include <vector>

struct LCA {
    std::vector<int> first, height, euler, segment;
    std::vector<bool> visited;

    LCA(std::vector<std::vector<int>>& adj, int root = 0) {
        size_t size{adj.size()};
        first.resize(size);
        height.resize(size);
        visited.resize(size);
        visited.assign(size, false);
        euler.reserve(2 * size);
        dfs(root, adj);
        size_t m{euler.size()};
        segment.resize(4 * m);
        build(1, 0, m - 1);
    }

    void dfs(int node, std::vector<std::vector<int>>& adj, int h = 0) {
        visited[node] = true;
        height[node] = h;
        first[node] = euler.size();
        euler.push_back(node);
        for (int to : adj[node]) {
            if (!visited[to]) {
                dfs(to, adj, h + 1);
            }
            euler.push_back(node);
        }
    }

    void build(int node, int l, int r) {
        if (l == r) {
            segment[node] = euler[l];
        } else {
            int tm{(l + r) >> 1};
            build(node << 1, l, tm);
            build(node << 1 | 1, tm + 1, r);
            int left = segment[node << 1];
            int right = segment[node << 1 | 1];
            segment[node] = height[left] < height[right] ? left : right;
        }
    }
    int query(int node, int tl, int tr, int l, int r) {
        if (tr < l || tl > r) {
            return -1;
        }
        if (tl >= l && tr <= r) {
            return segment[node];
        } else {
            int tm{(tl + tr) >> 1};
            int left = query(node << 1, tl, tm, l, r);
            int right = query(node << 1 | 1, tm + 1, tr, l, r);
            if (left == -1) return right;
            if (right == -1) return left;
            return height[left] < height[right] ? left : right;
        }
    }

    int lca(int u, int v) {
        int left{first[u]};
        int right{first[v]};
        if (left > right) {
            std::swap(left, right);
        }
        return query(1, 0, euler.size() - 1, left, right);
    }
};
int main() {

    /*
            1
           /|\
          2 3 4
         /\   |
        5  6  7
     */
    std::vector<std::vector<int>> adj{{},     {2, 3, 4}, {5, 6, 1}, {1},
                                      {7, 1}, {2},       {2},       {4}};
    LCA obj(adj, 1);
    std::cout << "LCA(5, 6): " << obj.lca(5, 6) << std::endl;
    std::cout << "LCA(2, 7): " << obj.lca(2, 7) << std::endl;
    std::cout << "LCA(6, 4): " << obj.lca(6, 4) << std::endl;
    return EXIT_SUCCESS;
}
