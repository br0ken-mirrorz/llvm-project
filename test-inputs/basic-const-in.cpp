#include <iostream>
using namespace std;

__attribute__((noinline)) int foo(int a,int b) {
    if (a<b) return 1;
    else return 0;
}

int main() {
    int c=5, d=10;
    return foo(c,d);
}