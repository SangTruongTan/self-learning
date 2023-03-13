#include <iostream>

int main() {
    int arr[] = {1, 2, 3, 4, 6};
    int sum = 0;
    sum += arr[0];
    sum += arr[1];
    sum += arr[2];
    sum += arr[3];
    sum += arr[4];
    float ret = (float) sum / 5;
    std::cout << "Avarage:" << ret << std::endl;
    return(0);
}