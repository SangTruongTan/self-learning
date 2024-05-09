/**
 * @file main.cpp
 * @author Sang Tan Truong (sang.truong@outlook.com.vn)
 * @brief OrOasis
 * @link
 * https://www.hackerearth.com/practice/algorithms/graphs/graph-representation/practice-problems/algorithm/uniformity-794d7bdc/
 * @version 0.1
 * @date 2024-05-08
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <cassert>
#include <ctime>
#include <iostream>

#include <algorithm>
#include <vector>
// #include <bits/stdc++.h>

#define TEST

void ind() {}

void outd() {}

void solve() {
    int N, K;
    std::cin >> N >> K;
    assert(N >= 1 && N <= 1e6);
    assert(K >= 0 && K <= N);
    std::string arr;
    std::cin >> arr;

    int l{0};
    int r{-1};
    int c1{0};
    int c2{0};
    int c3{0};
    int ans{0};
    std::vector<int> temp(3);
    while (l < N) {
        while(r < N - 1) {
            r++;
            assert(arr[r] == 'a' || arr[r] == 'b' || arr[r] == 'c');
            if (arr[r] == 'a') {
                c1++;
            } else if (arr[r] == 'b') {
                c2++;
            } else {
                c3++;
            }

            temp[0] = c1;
            temp[1] = c2;
            temp[2] = c3;
            std::sort(temp.begin(), temp.end());

            int mi = temp[0] + temp[1];
            if (mi > K) {
                break;
            }
            ans = std::max(ans, c1 + c2 + c3);
        }
        if (arr[l] == 'a') {
            c1--;
        } else if (arr[l] == 'b') {
            c2--;
        } else {
            c3--;
        }
        l++;
    }
    std::cout << ans << std::endl;
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
