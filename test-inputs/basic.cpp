#include <iostream>
#include <cassert>
int average(int a, int b);
int __attribute__((noinline)) average(int a, int b) {
    return (a + b) / 2;
}
void bar(int a, int b) {
    assert(0 <= a && a <= 10);
    assert(30 <= b && b <= 40);
    int x = average(a, b); // x is still in [15, 25]
    if (x < a) std::cout << "less than a!\n";
    if (x > b) std::cout << "more than b!\n";
    std::cout << "neither!\n";
}
