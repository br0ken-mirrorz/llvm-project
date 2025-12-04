#include <iostream>
using namespace std;

__attribute__((noinline)) int foo(int a, int b) {
    if (a<b) return b;
    if (a>b) return 1;
    else return 0;
}

int main() {
    int a=5,b=10;
    //cin >> a >> b;
    int x=foo(a,b);
    if (x==b) return x;
    else return -20;


}