#include <cassert>
int average(int a, int b);
int __attribute__((noinline)) average(int a, int b) {
    return (a + b) / 2;
}
int bar() {
    int a=5,b=10;
    int x = average(a, b); 
    if (x < a) return 1;
    if (x > b) return 2;
    else return 0;
}