/**
 * @file main.cpp
 * @author Sang Tan Truong (sang.truong@outlook.com.vn)
 * @brief Understanding
 * @link
 * https://www.hackerearth.com/practice/algorithms/graphs/breadth-first-search/tutorial/
 * @version 0.1
 * @date 2024-05-24
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <cassert>
#include <ctime>
#include <iostream>

#include <queue>
#include <vector>
// #include <bits/stdc++.h>

// #define TEST

void ind() {}

void outd() {}

void solve() {
    int N, x;

    std::cin >> N;
    assert(N >= 1 && N <= 1e5);
    std::vector<std::vector<int>> edges(N + 1);
    for (int i = 0; i < N - 1; i++) {
        int a, b;
        std::cin >> a >> b;
        assert(a >= 1 && a <= N);
        assert(b >= 1 && b <= N);
        edges[a].push_back(b);
        edges[b].push_back(a);
    }
    std::cin >> x;

    if (x == 1) {
        std::cout << 1 << std::endl;
        return;
    }
    int currentLayer{2};
    int numberOfNode{0};
    // BFS
    std::vector<bool> visited(N, false);
    std::queue<int> q{};
    q.push(1);
    visited[1] = true;
    while (!q.empty()) {

        size_t size{q.size()};
        while (size-- > 0) {
            int node{q.front()};
            q.pop();

            for (int newNode : edges[node]) {
                if (visited[newNode] == false) {
                    q.push(newNode);
                    visited[newNode] = true;
                    if (currentLayer == x) {
                        // std::cout << newNode << std::endl;
                        numberOfNode += 1;
                    }
                }
            }
        }

        if (currentLayer == x) {
            break;
        }
        currentLayer += 1;
    }
    std::cout << numberOfNode << std::endl;
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
