#include <iostream>

#include <algorithm>

using namespace std;
////

int main() {
    int n;
    cin >> n;
    int cnt = 0;
    for (int a = 1; a <= n; a++){
        for (int b = a; b <= n; b++){
            for (int c = max(a, b) - min(a, b) + 1; c < min(a + b, n); c++) {
                if ((a ^ b ^ c) == 0 and a <= c and c <= b){
                    cnt++;
                }
            }
        }
    }
    cout << cnt;
}