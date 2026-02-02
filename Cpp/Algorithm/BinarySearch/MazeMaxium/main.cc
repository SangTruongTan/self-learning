/**
 * @file main.cpp
 * @author Sang Tan Truong (sang.truong@outlook.com.vn)
 * @brief Assignment Problem - Maze Maximum
 * @link
 * https://www.hackerearth.com/practice/algorithms/searching/binary-search/practice-problems/algorithm/maze-maximum-8f0fa284/
 * @version 0.1
 * @date 2026-02-02
 *
 * @copyright Copyright (c) 2026
 *
 */
#include <cassert>
#include <ctime>
#include <iostream>

#include <limits>
#include <vector>

using namespace std;

void ind() {}

void outd() {}

void solve() {
    int N, M;
    cin >> N >> M;
    int arr[N + 1][M + 1];
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            cin >> arr[i][j];
        }
    }

    int ans = -1;
    int start = 1;
    int end = 1000000000;
    while (start <= end) {
        int mid = (start + end) / 2;
        bool valid_row{false};
        bool valid_col{false};
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= M; j++) {
                if (arr[i][j] < mid) {
                    break;
                }
                if (j == M) {
                    valid_col = true;
                }
            }
        }
        for (int i = 1; i <= M; i++) {
            for (int j = 1; j <= N; j++) {
                if (arr[j][i] < mid) {
                    break;
                }
                if (j == N) {
                    valid_row = true;
                }
            }
        }
        if (valid_col && valid_row) {
            ans = mid;
            start = mid + 1;
        } else {
            end = mid - 1;
        }
    }
    cout << ans << endl;
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
