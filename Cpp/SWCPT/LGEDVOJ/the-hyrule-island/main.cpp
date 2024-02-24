#include <iostream>
#include <queue>
#include <tuple>
#include <vector>
#include <cstring>

const int R_MAX = 100;
const int C_MAX = 100;
const int N_MAX = 9;

char grid[R_MAX][C_MAX];
int dist[R_MAX][C_MAX][1 << N_MAX];

int R, C, N;

int bfs(int r, int c, int mask) {
    memset(dist, -1, sizeof(dist));
    std::queue<std::tuple<int, int, int>> q;
    q.emplace(r, c, mask);
    int m, n, mas;
    dist[r][c][mask] = 0;
    while (!q.empty()) {
        std::tie(m, n, mas) = q.front();
        q.pop();
        if (mas == (1 << N) - 1) {
            return dist[m][n][mas];
        }
        for (int dr = -1; dr <= 1; ++dr) {
            for (int dc = -1; dc <= 1; ++dc) {
                if (abs(dr) + abs(dc) == 1) {
                    int nr = m + dr;
                    int nc = n + dc;
                    int nmask = mas;
                    if (nc >= 0 && nr >= 0 && nc < C && nr < R) {
                        if (grid[nr][nc] == '.') {
                            // Empty place
                        } else if (grid[nr][nc] == '#') {
                            // Mountain
                            continue;
                        } else {
                            int shrimp = grid[nr][nc] - '1';
                            nmask |= 1 << shrimp;
                        }
                        if (dist[nr][nc][nmask] == -1) {
                            dist[nr][nc][nmask] = dist[m][n][mas] + 1;
                            q.emplace(nr, nc, nmask);
                        }
                    }
                }
            }
        }
    }
    return -1;
}

int solve() {
    int max = -1;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (isdigit(grid[i][j])) {
                int c = grid[i][j] - '1';
                max = (max == -1) ? bfs(i, j, 1 << c)
                                  : std::min(max, bfs(i, j, 1 << c));
            }
        }
    }
    return max;
}

int main(int argc, char *argv[]) {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    clock_t start = clock();
    /* Start User Code */
    std::cin >> R >> C >> N;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            std::cin >> grid[i][j];
        }
    }
    std::cout << solve() << std::endl;
    /* End User Code */
    clock_t stop = clock();
    printf("\rTime taken:%fs",
           static_cast<double>(stop - start) / CLOCKS_PER_SEC);
    return (0);
}
