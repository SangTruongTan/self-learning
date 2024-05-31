/**
 * @file main.cc
 * @author Sang Tan Truong (sang.truong@outlook.com.vn)
 * @brief Heaps
 * @link
 * https://www.hackerearth.com/practice/algorithms/sorting/heap-sort/practice-problems/algorithm/heaps/
 * @version 0.1
 * @date 2024-05-29
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <cassert>
#include <ctime>
#include <iostream>

#include <vector>
#include <stack>
// #include <bits/stdc++.h>

#ifndef NDEBUG
#define ASSERT(condition, message)                                             \
    do {                                                                       \
        if (!(condition)) {                                                    \
            std::cerr << "Assertion `" #condition "` failed in " << __FILE__   \
                      << " line " << __LINE__ << ": " << message << std::endl; \
            std::terminate();                                                  \
        }                                                                      \
    } while (false)
#else
#define ASSERT(condition, message)                                             \
    do {                                                                       \
    } while (false)
#endif

// #define TEST


void solve() {
    int N, M;

    std::cin >> N >> M;
    assert(N >= 1 && N <= 1e5);
    assert(M >= 1 && M <= 1e5);

    std::vector<std::vector<int>> adj(N + 1);

    int a, b, x;
    int numReachable{0};
    while(M--) {
        std::cin >> a >> b;
        assert(a >= 1 && a <= N);
        assert(b >= 1 && b <= N);

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    std::cin >> x;

    std::stack<int> stk{};
    std::vector<bool> visited(N + 1, false);
    stk.push(x);
    visited[x] = true;
    while(!stk.empty()) {
        int node{stk.top()};
        stk.pop();
        numReachable += 1;
        for (int newNode : adj[node]) {
            if (!visited[newNode]) {
                stk.push(newNode);
                visited[newNode] = true;
            }
        }
    }
    std::cout << (N - numReachable) << std::endl;
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
        solve();
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
