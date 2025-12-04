#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
int __attribute__((noinline)) ex(int a, int b) {
    return (a + b) / 2;
}

int foo(int a, int b) {
    assert(0 <= a && a <= 10);
    assert(30 <= b && b <= 40);
    int x = ex(a, b);
    if (x < a) return 5;
    if (x > b) return 3;
    return 0;
}