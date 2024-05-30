/**
 * @file main.cc
 * @author Sang Tan Truong (sang.truong@outlook.com.vn)
 * @brief Segment Tree implementation
 * @link
 * https://cp-algorithms.com/data_structures/segment_tree.html#implementation
 * @version 0.1
 * @date 2024-05-30
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <iostream>

#include <algorithm>
#include <vector>

struct SegmentTree {
    std::vector<int> tree;
    int size;

    SegmentTree(std::vector<int>& arr) {
        size = arr.size();
        tree.resize(4 * size);
        build(arr, 1, 0, size - 1);
    }

    void build(std::vector<int>& arr, int v, int tl, int tr) {
        if (tl == tr) {
            tree[v] = arr[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(arr, v * 2, tl, tm);
            build(arr, v * 2 + 1, tm + 1, tr);
            tree[v] = tree[v * 2] + tree[v * 2 + 1];
        }
    }

    int sum(int l, int r) { return sum(1, 0, size - 1, l, r); }

    int sum(int v, int tl, int tr, int l, int r) {
        if (l > r) {
            return 0;
        }
        if (tl == l && tr == r) {
            return tree[v];
        } else {
            int tm{(tl + tr) / 2};
            return sum(v * 2, tl, tm, l, std::min(r, tm)) +
                   sum(v * 2 + 1, tm + 1, tr, std::max(l, tm + 1), r);
        }
    }

    void showTree() {
        for (int i = 0; i < tree.size(); i++) {
            std::cout << tree[i] << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    std::vector<int> arr{-1, 2, 5, 7, 9};
    SegmentTree obj(arr);
    obj.showTree();
    std::cout << obj.sum(2, 4) << std::endl;
    return EXIT_SUCCESS;
}
