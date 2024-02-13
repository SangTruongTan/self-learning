#include <functional>
#include <iostream>

class B {
public:
    std::function<void(int, int)> func;
};
class A {
public:
    int b = 5;
    B classB;
    static void funcA(int b, int c, int d) { std::cout << c << "b value:" << b << d << std::endl; }
};



int main() {
    A a;
    a.classB.func = std::bind(A::funcA, a.b, std::placeholders::_1, std::placeholders::_2);
    a.classB.func(3, 5);
    return 0;
}
