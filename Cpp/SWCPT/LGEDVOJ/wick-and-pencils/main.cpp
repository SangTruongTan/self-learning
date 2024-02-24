#include <iostream>
#include <vector>

long get_number_triangle(int N, std::vector<int> &vec) {
    long num = 0;
    std::sort(vec.begin(), vec.end());
    for (int i = N - 1; i > 1; i--) {
        int j = i - 1;
        int k = 0;
        while(j > k) {
            if (vec[j] + vec[k] > vec[i]) {
                num += j - k;
                j--;
            } else {
                k++;
            }
        }
    }
    return num;
}

int main(int argc, char *argv[]) {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    time_t start = clock();
    /* Start User Code */
    int N;
    std::cin >> N;
    std::vector<int> vec(N);
    for (int i = 0; i < N; i++) {
        std::cin >> vec[i];
    }
    std::cout << get_number_triangle(N, vec) << std::endl;
    /* End User Code */
    time_t stop = clock();
    printf("Time taken:%fs\r",
           static_cast<double>(stop - start) / CLOCKS_PER_SEC);
    return (0);
}
