/**
 * @file main.cpp
 * @author Sang Tan Truong (sang.truong@outlook.com.vn)
 * @brief City Tour
 * @link
 * https://codejam.lge.com/contest/problem/1251/2
 * @version 0.1
 * @date 2024-08-09
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <algorithm>
#include <climits>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

// Function to calculate the minimum and maximum travel times
pair<int, int> calculateTravelTimes(int N, vector<vector<vector<int>>> &D) {
    // dp[mask][i][trans_mask] will store the minimum and maximum travel time to
    // visit the cities represented by 'mask', ending in city 'i' with
    // transportation methods used represented by 'trans_mask'
    vector<vector<vector<pair<int, int>>>> dp(
        1 << N, vector<vector<pair<int, int>>>(
                    N, vector<pair<int, int>>(1 << N, {INT_MAX, INT_MIN})));

    // Initialize starting city with 0 travel time
    // for (int i = 0; i < N; ++i) {
    //     dp[1][0][1 << i] = 0;
    // }
    dp[1][0][0] = {0, 0};
    // Iterate over all subsets of cities
    for (int mask = 1; mask < (1 << N); ++mask) {
        for (int last = 0; last < N; ++last) {
            if (!(mask & (1 << last)))
                continue; // last must be in the subset represented by mask
            for (int trans_mask = 0; trans_mask < (1 << N); ++trans_mask) {
                int flagMin{true};
                int flagMax{true};
                if (dp[mask][last][trans_mask].first == INT_MAX) {
                    // continue;                 // Skip if no path
                    flagMin = false;
                }
                if (dp[mask][last][trans_mask].second == INT_MIN) {
                    // continue;                 // Skip if no path
                    flagMax = false;
                }

                if (flagMin == false && flagMax == false) continue;
                for (int k = 0; k < N; ++k) { // k-th transportation method
                    if (trans_mask & (1 << k))
                        continue; // Skip if transportation method already used
                    for (int next = 0; next < N; ++next) {
                        if (mask & (1 << next))
                            continue; // next must not be in the subset
                        int nextMask = mask | (1 << next);
                        int nextTransMask = trans_mask | (1 << k);
                        if (D[k][last][next] > 0) {
                            // Calculate min
                            if (flagMin) {
                                dp[nextMask][next][nextTransMask].first =
                                    min(dp[nextMask][next][nextTransMask].first,
                                        dp[mask][last][trans_mask].first +
                                            D[k][last][next]);
                                // cout << nextMask << "|" << nextTransMask << "|"
                                //      << next << "|"
                                //      << dp[nextMask][next][nextTransMask].first
                                //      << endl;
                            }
                            // Calculate max
                            if (flagMax) {
                                dp[nextMask][next][nextTransMask].second = max(
                                    dp[nextMask][next][nextTransMask].second,
                                    dp[mask][last][trans_mask].second +
                                        D[k][last][next]);
                                // cout << nextMask << "|" << nextTransMask <<
                                // "|"
                                //      << next << "|"
                                //      <<
                                //      dp[nextMask][next][nextTransMask].second
                                //      << endl;
                            }
                        }
                    }
                }
            }
        }
    }

    // Find the minimum and maximum travel times including the return to the
    // first city
    int minTime = INT_MAX, maxTime = INT_MIN;
    int fullMask = (1 << N) - 1;
    // cout << "Fullmask:" << fullMask << endl;
    for (int last = 1; last < N; ++last) {
        for (int lastTransport = 0; lastTransport < N; lastTransport++) {
            int mask = (fullMask & (~(1 << lastTransport)));
            int returnTime =
                D[lastTransport][last][0]; // Time to return to the first
                                           // city using k-th transportation
            if (returnTime >
                0) { // Ensure there is a path back to the first city
                // cout << "Mask:" << mask << endl;
                if (dp[fullMask][last][mask].first != INT_MAX) {
                    // cout << "I'm here" << endl;
                    minTime = min(minTime,
                                  dp[fullMask][last][mask].first + returnTime);
                }
                if (dp[fullMask][last][mask].second != INT_MIN) {
                    // cout << "I'm here\n";
                    maxTime = max(maxTime,
                                  dp[fullMask][last][mask].second + returnTime);
                }
            }
        }
    }
    if (minTime == INT_MAX) return {0, 0};
    return {minTime, maxTime};
}

void solve() {
    int N;
    cin >> N;

    // 3D vector to store weights for each method, starting city, and ending
    // city
    vector<vector<vector<int>>> weights(N,
                                        vector<vector<int>>(N, vector<int>(N)));

    // Input weights
    for (int method = 0; method < N; ++method) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                cin >> weights[method][i][j];
            }
        }
    }

    auto [minTime, maxTime] = calculateTravelTimes(N, weights);
    // cout << "Minimum travel time: " << minTime << endl;
    // cout << "Maximum travel time: " << maxTime << endl;

    cout << minTime << " " << maxTime << endl;
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
    std::cin >> T;
    while (T--) {
        // ind();
        solve();
        // outd();
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
