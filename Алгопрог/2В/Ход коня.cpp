#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
int main() {
    int n;
    cin >> n;
    vector<long long> a(n + 1);
    a[1] = 8;
    a[2] = 16; // 16   
    a[3] = 12 * 2 + 4 * 3; // 36
    a[4] = 20 * 2 + 16 * 3; // 88 
    a[5] = 40 * 2 + 36 * 3; // 188
    for (int i = 6; i <= n; i++) {
        a[i] = a[i - 2] * 3 + (a[i - 1] - a[i - 3] * 3) * 2;
    }
    cout << a[n];
}