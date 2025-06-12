#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int gcd(int a, int b){
    while (b){
        a = a % b;
        swap(a, b);
    }
    return a;
}

int main(){
    int a, b, c;
    cin >> c;
    int maxgcd = 0;
    for (int i = 1; i < c; i++){
        int x = gcd(i, c - i);
        if (x > maxgcd) {
            maxgcd = x;
            a = i;
            b = c - i;
        }
    }
    cout << a << " " << b;
}