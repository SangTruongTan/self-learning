/**
 * @file main.cpp
 * @author Sang Tan Truong (sang.truong@outlook.com.vn)
 * @brief Cryptic Line
 * @link
 * https://www.hackerearth.com/practice/algorithms/graphs/depth-first-search/practice-problems/algorithm/cryptic-line-92a6bd09/
 * @version 0.1
 * @date 2024-05-24
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <cassert>
#include <ctime>
#include <iostream>

#include <limits>
#include <queue>
#include <utility>
#include <vector>
// #include <bits/stdc++.h>

// #define TEST

void ind() {}

void outd() {}

void solve() {
    int32_t N, Q;
    int32_t U, V;
    int32_t X, Y;

    std::cin >> N >> Q;

    // std::cout << "N:" << N << std::endl;
    assert(N >= 1 && N <= 2e5);
    assert(Q >= 1 && Q <= 2e5);

    std::vector<std::vector<int32_t>> input(N + 1);
    std::vector<std::vector<int32_t>> ancestralConnection(N + 1);

    for (int32_t i = 0; i < N - 1; i++) {
        std::cin >> U >> V;
        assert(U >= 1 && U <= N);
        assert(V >= 1 && V <= N);
        input[U].push_back(V);
        input[V].push_back(U);
    }

    std::queue<int32_t> que{};
    std::vector<bool> visited(N + 1, false);
    que.push(1);
    visited[1] = true;
    while (!que.empty()) {
        int32_t node{que.front()};
        que.pop();

        for (int next : input[node]) {
            if (visited[next] == false) {
                ancestralConnection[node].push_back(next);
                que.push(next);
                visited[next] = true;
            }
        }
    }

    while (Q--) {
        std::cin >> X >> Y;

        std::queue<int32_t> q{};
        q.push(X);
        std::string ans{"NO"};
        if (X == Y) {
            goto done;
        }
        while (!q.empty()) {
            int32_t curPer{q.front()};
            q.pop();

            for (int32_t nextGen : ancestralConnection[curPer]) {
                if (nextGen == Y) {
                    ans = "YES";
                    goto done;
                }
                q.push(nextGen);
            }
        }
    done:
        std::cout << ans << std::endl;
    }
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
