/**
 * @file main.cc
 * @author Sang Tan Truong (sang.truong@outlook.com.vn)
 * @brief Dijkstra's Algorithm
 * @link
 * https://brilliant.org/wiki/dijkstras-short-path-finder/
 * @version 0.1
 * @date 2024-06-04
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <cassert>
#include <ctime>
#include <iostream>

#include <algorithm>
#include <limits>
#include <queue>
#include <stack>
#include <tuple>
#include <vector>
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
int X_SIZE{20};
int Y_SIZE{20};

// W -> N -> E -> S
int dir_x[] = {-1, 0, 1, 0};
int dir_y[] = {0, 1, 0, -1};

char daddy = 'D';
char sally = 'S';
char wall = '#';
typedef std::tuple<int, int, int, int, int> node;
typedef std::pair<int, int> ii;

bool x_isOutOfBound(int x) { return (x >= X_SIZE || x < 0); }

bool y_isOutOfBound(int y) { return (y >= X_SIZE || y < 0); }

std::priority_queue<node, std::vector<node>, std::greater<node>> pq;
std::vector<std::vector<int>> nodeWeight;
std::vector<std::vector<ii>> nodeParent;
std::vector<ii> visitedNode;

std::vector<std::vector<char>> maps;
bool found = false;

ii posDaddy;
ii posSally;

void init() {
    maps.resize(X_SIZE);
    nodeWeight.resize(X_SIZE);
    nodeParent.resize(X_SIZE);
    for (int r = 0; r < X_SIZE; r++) {
        maps[r].resize(Y_SIZE);
        nodeWeight[r].resize(Y_SIZE);
        nodeParent[r].resize(Y_SIZE);
    }
}

int solve() {
    // Reinitialize
    pq = std::priority_queue<node, std::vector<node>, std::greater<node>>();
    visitedNode.clear();
    visitedNode = std::vector<ii>();

    for (int r = 0; r < X_SIZE; r++) {
        for (int c = 0; c < Y_SIZE; c++) {
            nodeWeight[r][c] = std::numeric_limits<int>::max();
        }
    }

    for (int r = 0; r < X_SIZE; r++) {
        for (int c = 0; c < Y_SIZE; c++) {
            std::cin >> maps[r][c];
            if (maps[r][c] == daddy) {
                posDaddy = std::make_pair(r, c);
            } else if (maps[r][c] == sally) {
                posSally = std::make_pair(r, c);
            }
        }
    }

    // Dijkstra's Algorithm
    pq.push(std::make_tuple(0, posSally.first, posSally.second, posSally.first,
                            posSally.second));
    nodeWeight[posSally.first][posSally.second] = 0;

    while (!pq.empty()) {
        auto [weight, pos_x, pos_y, parent_x, parent_y] = pq.top();
        pq.pop();

        ii pos{std::make_pair(pos_x, pos_y)};
        ii parent{std::make_pair(parent_x, parent_y)};
        found = (std::find(visitedNode.begin(), visitedNode.end(), pos) !=
                 visitedNode.end());

        if (found) continue;

        visitedNode.push_back(pos);

        nodeParent[pos_x][pos_y] = parent;

        if (pos == posDaddy) {
            break;
        }

        if (weight > nodeWeight[pos_x][pos_y]) continue;

        for (int i = 0; i < sizeof(dir_x) / sizeof(dir_x[0]); i++) {

            int temp_x{pos_x + dir_x[i]};
            int temp_y{pos_y + dir_y[i]};
            ii temp_pos{pos_x, pos_y};
            int temp_weight(weight);
            while (!x_isOutOfBound(temp_x) && !y_isOutOfBound(temp_y) &&
                   maps[temp_x][temp_y] != wall) {
                temp_pos = std::make_pair(temp_x, temp_y);
                temp_weight += 1;
                temp_x += dir_x[i];
                temp_y += dir_y[i];
            }

            found = (std::find(visitedNode.begin(), visitedNode.end(),
                               temp_pos) != visitedNode.end());
            if (!x_isOutOfBound(temp_pos.first) &&
                !y_isOutOfBound(temp_pos.second) &&
                maps[temp_pos.first][temp_pos.second] != wall &&
                temp_pos != pos && found == false) {
                if (temp_weight < nodeWeight[temp_pos.first][temp_pos.second]) {
                    pq.push(std::make_tuple(temp_weight, temp_pos.first,
                                            temp_pos.second, pos_x, pos_y));
                    nodeWeight[temp_pos.first][temp_pos.second] = temp_weight;
                }
            }
        }
    }
    // Draw the path
    ii curNode{posDaddy};
    auto [parent_x, parent_y] = nodeParent[curNode.first][curNode.second];
    int count = 0;
    while (curNode != posSally) {
        auto [parent_x, parent_y] = nodeParent[curNode.first][curNode.second];
        if (count++ > 200) break;

        int bias_x{parent_x - curNode.first};
        int bias_y{parent_y - curNode.second};

        if (bias_x > 0) {
            bias_x = 1;
        } else if (bias_x < 0) {
            bias_x = -1;
        }

        if (bias_y > 0) {
            bias_y = 1;
        } else if (bias_y < 0) {
            bias_y = -1;
        }

        while (curNode.first != parent_x || curNode.second != parent_y) {
            if (maps[curNode.first][curNode.second] != daddy) {
                maps[curNode.first][curNode.second] = 'x';
            }
            curNode.first += bias_x;
            curNode.second += bias_y;
        }
    }

    for (int r = 0; r < X_SIZE; r++) {
        for (int c = 0; c < Y_SIZE; c++) {
            std::cout << maps[r][c];
        }
        std::cout << std::endl;
    }

    std::cout << "Result:" << nodeWeight[posDaddy.first][posDaddy.second]
              << std::endl;
    std::cout << "\n--------------------\n\n";

    return nodeWeight[posDaddy.first][posDaddy.second];
}

#ifdef TEST
int main1() {
#else
int main() {
#endif
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int T{5};
    int sumSteps{0};
    std::string dummy;
    init();
    while (T--) {
        sumSteps += solve();
        std::getline(std::cin, dummy);
        std::getline(std::cin, dummy);
    }
    std::cout << sumSteps << std::endl;
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
