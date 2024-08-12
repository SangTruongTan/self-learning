/**
 * @file main.cpp
 * @author Sang Tan Truong (sang.truong@outlook.com.vn)
 * @brief City Tour
 * @link
 * https://codejam.lge.com/contest/problem/1251/4
 * @version 0.1
 * @date 2024-08-10
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <cstring>
#include <iostream>
#include <vector>

#define MOD 1000000007
using namespace std;
const int MAXN = 65005;

vector<int> adjA[MAXN], adjB[MAXN];
int specialA[MAXN], specialB[MAXN];

long long dp1A[MAXN];
long long dp2A[MAXN];
long long dp3A[MAXN];

long long dp1B[MAXN];
long long dp2B[MAXN];
long long dp3B[MAXN];

void dfs1(int node, int parent, vector<int> adj[], int special[], long long dp1[],
          long long dp2[], long long dp3[]) {
    dp1[node] = special[node];
    dp3[node] = !special[node];
    for (int neighbor : adj[node]) {
        if (neighbor == parent) continue;
        dfs1(neighbor, node, adj, special, dp1, dp2, dp3);
        if (special[node]) {
            dp2[node] += dp3[neighbor];
        } else {
            dp1[node] += dp1[neighbor];
            dp2[node] += dp2[neighbor];
            dp3[node] += dp3[neighbor];
        }
    }
}

void dfs2(int node, int parent, vector<int> adj[], int special[], long long dp1[],
          long long dp2[], long long dp3[]) {
    for (int neighbor : adj[node]) {
        if (neighbor == parent) continue;
        // NS - NS
        if (!special[node] && !special[neighbor]) {
            dp1[neighbor] = dp1[node];
            dp2[neighbor] = dp2[node];
            dp3[neighbor] = dp3[node];
        } else if (!special[node] && special[neighbor]) {
            // NS - S
            dp1[neighbor] = 1;
            dp2[neighbor] += dp3[node];
            dp3[neighbor] = 0;
        } else if (special[node] && !special[neighbor]) {
            // S - NS
            dp1[neighbor] += dp1[node];
            dp2[neighbor] += dp2[node] - dp3[neighbor];
        } else {
            // S - S
            // Hold
        }
        dfs2(neighbor, node, adj, special, dp1, dp2, dp3);
    }
}

void solve() {
    int NA, SA, NB, SB;
    cin >> NA >> SA;

    memset(specialA, 0, sizeof(specialA));
    for (int i = 0; i < SA; i++) {
        int x;
        cin >> x;
        specialA[x] = 1;
    }

    for (int i = 1; i <= NA; i++)
        adjA[i].clear();

    for (int i = 0; i < NA - 1; i++) {
        int u, v;
        cin >> u >> v;
        adjA[u].push_back(v);
        adjA[v].push_back(u);
    }

    cin >> NB >> SB;

    memset(specialB, 0, sizeof(specialB));
    for (int i = 0; i < SB; i++) {
        int x;
        cin >> x;
        specialB[x] = 1;
    }

    for (int i = 1; i <= NB; i++)
        adjB[i].clear();

    for (int i = 0; i < NB - 1; i++) {
        int u, v;
        cin >> u >> v;
        adjB[u].push_back(v);
        adjB[v].push_back(u);
    }

    memset(dp1A, 0, sizeof(dp1A));
    memset(dp2A, 0, sizeof(dp2A));
    memset(dp3A, 0, sizeof(dp3A));

    memset(dp1B, 0, sizeof(dp1B));
    memset(dp2B, 0, sizeof(dp2B));
    memset(dp3B, 0, sizeof(dp3B));

    dfs1(1, -1, adjA, specialA, dp1A, dp2A, dp3A);
    dfs2(1, -1, adjA, specialA, dp1A, dp2A, dp3A);

    dfs1(1, -1, adjB, specialB, dp1B, dp2B, dp3B);
    dfs2(1, -1, adjB, specialB, dp1B, dp2B, dp3B);
    // for (int i = 1; i <= NB; i++) {
    //     cout << i << "==> " << dp1A[i] << ":" << dp2A[i] << ":" << dp3A[i]
    //          << endl;
    // }

    // long long result = 0;

    // for (int i = 1; i <= NA; i++) {
    //     for (int j = 1; j <= NB; j++) {
    //         long long paths = 1LL * (dp1A[i] + dp2A[i]) * (dp1B[j] + dp2B[j])
    //         ; result = (result + paths * (i + j)) % MOD;
    //     }
    // }
    long long result = 0;

    long long sumA = 0, sumB = 0;
    long long sumAi = 0, sumBj = 0;

    for (int i = 1; i <= NA; i++) {
        sumA = (sumA + dp1A[i] + dp2A[i]) % MOD;
        sumAi = (sumAi + i * (dp1A[i] + dp2A[i])) % MOD;
    }

    for (int j = 1; j <= NB; j++) {
        sumB = (sumB + dp1B[j] + dp2B[j]) % MOD;
        sumBj = (sumBj + j * (dp1B[j] + dp2B[j])) % MOD;
    }

    // Now calculate the result using the precomputed sums
    long long sum1 = (sumAi * sumB) % MOD;
    long long sum2 = (sumBj * sumA) % MOD;
    result = (sum1 + sum2) % MOD;

    cout << result << endl;
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
    ::printf("Time taken: %.10fs\n",
             (double)(::clock() - tStart) / CLOCKS_PER_SEC);
    ::fclose(stdin);
    ::fclose(stdout);
    return EXIT_SUCCESS;
}
#endif
