#include <iostream>
using namespace std;

__attribute__((noinline)) int foo(int a,int b) {
    if (a<b) return 1;
    else return 0;
}

int main() {
    int c=5, d=10;
    int x = foo(c,d);
    if (x==1) return 5;
    return 0;
}