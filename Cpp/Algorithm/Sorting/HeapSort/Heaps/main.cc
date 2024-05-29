/**
 * @file main.cc
 * @author Sang Tan Truong (sang.truong@outlook.com.vn)
 * @brief Heaps
 * @link
 * https://www.hackerearth.com/practice/algorithms/sorting/heap-sort/practice-problems/algorithm/heaps/
 * @version 0.1
 * @date 2024-05-29
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <cassert>
#include <ctime>
#include <iostream>

#include <vector>
// #include <bits/stdc++.h>

// #define TEST

struct MaxHeap {
    std::vector<int> heap;
    int mSize;
    int size;
    MaxHeap(int size) : mSize(size), size(0) { heap.reserve(mSize); }

    void insert(int num) {
        size += 1;
        if (size > mSize) {
            assert(false);
        }

        heap[size - 1] = num;

        int i{size - 1};

        while (i != 0 && heap[parentIndex(i)] < heap[i]) {
            std::swap(heap[parentIndex(i)], heap[i]);
            i = parentIndex(i);
        }
    }

    int parentIndex(int node) { return (node - 1) / 2; }

    int extractMax() {
        if (size < 1) {
            assert(false);
        }
        if (size == 1) {
            size -= 1;
            return heap[0];
        }
        int root = heap[0];
        heap[0] = heap[size - 1];
        size -= 1;
        maxHeapify(0);
        return root;
    }

    void maxHeapify(int index) {
        int left{index * 2 + 1};
        int right{index * 2 + 2};

        int largest{index};
        if (left < size && heap[left] > heap[index]) {
            largest = left;
        }

        if (right < size && heap[right] > heap[largest]) {
            largest = right;
        }
        if (largest != index) {
            std::swap(heap[largest], heap[index]);
            maxHeapify(largest);
        }
    }

    std::vector<int> getTopThree() {
        std::vector<int> retval{-1};
        if (size >= 3) {
            retval.assign({});
            retval.push_back(extractMax());
            retval.push_back(extractMax());
            retval.push_back(extractMax());
            insert(retval[0]);
            insert(retval[1]);
            insert(retval[2]);
        }
        return retval;
    }
};

void solve() {
    int T, X;
    std::cin >> T;
    assert(T >= 1 && T <= 1e5);
    MaxHeap hp(T);

    while (T--) {
        std::cin >> X;
        hp.insert(X);

        std::vector<int> top{hp.getTopThree()};
        if (top.size() == 3) {
            std::cout << top[0] << " " << top[1] << " " << top[2] << std::endl;
        } else {
            std::cout << top[0] << std::endl;
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
        solve();
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
