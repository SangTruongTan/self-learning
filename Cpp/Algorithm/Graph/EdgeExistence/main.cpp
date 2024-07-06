/**
 * @file main.cpp
 * @author Sang Tan Truong (sang.truong@outlook.com.vn)
 * @brief OrOasis
 * @link
 * https://www.hackerearth.com/practice/algorithms/graphs/graph-representation/tutorial/
 * @version 0.1
 * @date 2024-05-07
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <cassert>
#include <ctime>
#include <iostream>

#include <map>
#include <stack>
#include <vector>
// #include <bits/stdc++.h>

#define TEST

void ind() {}

void outd() {}

void solve() {
    int N, M;
    int Q;

    std::cin >> N >> M;
    assert(N >= 1 && N <= 1e3);
    assert(M >= 1 && M <= 1e3);

    int adj[N][N];
    int A, B;
    for (int i = 0; i < M; i++) {
        std::cin >> A >> B;
        assert(A >= 1 && A <= N);
        assert(B >= 1 && B <= N);
        adj[A][B] = 1;
        adj[B][A] = 1;
    }

    std::cin >> Q;
    assert(Q >= 1 && Q <= 1e3);

    while (Q--) {
        std::cin >> A >> B;
        assert(A >= 1 && A <= N);
        assert(B >= 1 && B <= N);

        if (adj[A][B] == 1 && adj[B][A] == 1) {
            std::cout << "YES" << std::endl;
        } else {
            std::cout << "NO" << std::endl;
        }
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
