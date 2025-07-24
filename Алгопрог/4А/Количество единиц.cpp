#include <iostream>

using namespace std;

int main() {
    unsigned long long x;
    cin >> x;
    int ans = 0;
    while (x != 0){
        ans += (x & 1);
        x = x >> 1;
    }
    cout << ans;
}