#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

int getScore(int n, std::vector<int> &A, std::vector<int> &B) {
    int res = 0;
    int tmp = 0;
    for (int i = 0; i < n; i++) {
        std::vector<int> A_new(A);
        A_new.erase(A_new.begin() + i);
        for (int j = 0; j < n; j++) {
            std::vector<int> B_new(B);
            B_new.erase(B_new.begin() + j);
            for (int k = 0; k < n - 1; k++) {
                if (A_new[k] == B_new[k]) {
                    tmp++;
                } else {
                    tmp = 0;
                }
                res = std::max(res, tmp);
            }
            tmp = 0;
        }
    }
    return res;
}

int main(int argc, char *argv[]) {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    clock_t start = clock();
    /* Start user code */
    int N;
    std::cin >> N;
    std::vector<int> A(N);
    std::vector<int> B(N);
    for (int i = 0; i < N; i++) {
        std::cin >> A[i];
    }
    for (int i = 0; i < N; i++) {
        std::cin >> B[i];
    }
    std::cout << getScore(N, A, B) << std::endl;
    /* End user code */
    clock_t end = clock();
    printf("\rTime token:%fs\r",
           static_cast<double>(end - start) / CLOCKS_PER_SEC);
    return (0);
}
