/**
 * @file main.cpp
 * @author Sang Tan Truong (sang.truong@outlook.com.vn)
 * @brief Assignment Problem - Longest Subsequence Queries
 * @link
 * https://www.hackerearth.com/practice/algorithms/searching/binary-search/practice-problems/algorithm/longest-subsequence-queries-9c45a765
 * @version 0.1
 * @date 2026-02-02
 *
 * @copyright Copyright (c) 2026
 *
 */
#include <cassert>
#include <ctime>
#include <iostream>

#include <algorithm>
#include <limits>
#include <vector>

using namespace std;

#define ll long long
void ind() {}

void outd() {}

void solve() {
    int n, q;
    cin >> n >> q;
    vector<ll> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    sort(arr.begin(), arr.end());
    vector<ll> presum(n);
    presum[0] = arr[0];
    for (int i = 1; i < n; i++) {
        presum[i] = presum[i - 1] + arr[i];
    }
    while (q--) {
        ll k;
        cin >> k;
        cout << lower_bound(presum.begin(), presum.end(), k) - presum.begin()
             << endl;
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
    int T;
    cin >> T;
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
