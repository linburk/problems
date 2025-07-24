#include <queue>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
using namespace std;

bool check(unsigned long long w, unsigned long long h, unsigned long long n, unsigned long long x){
    return ((x / w) * (x / h)) >= n;
}


unsigned long long bin(unsigned long long w, unsigned long long h, unsigned long long n){
    unsigned long long l = 0, r = w * h * n;
    while (r - l > 1){
        unsigned long long m = (r + l) / 2;
        if (check(w, h, n, m))
            r = m;
        else
            l = m;
    }
    return r;
}

int main(){
    unsigned long long w, h, n;
    cin >> w >> h >> n;
    cout << bin(w, h, n);
}