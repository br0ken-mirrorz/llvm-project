#include <iostream>
using namespace std;


int foo(int a,int b) {
    if (a<b) {
        int c=9;
        if (b<c) {
            if (a<c) return 1;
            else return 5;
        }
    } else return 0;
}