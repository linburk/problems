#include <iostream>
using namespace std;

bool check(int m, int n, int a, int b){
    return (a / m + b / m) >= n;
}

int bin_search(int n, int a, int b){
    int l = 1, r = 1e3;
    while (r - l > 1){
        int m = (l + r) / 2;
        if (check(m, n, a, b))
            l = m;
        else
            r = m;
    }
    return l;
}

int main() {
    int n, a, b;
    cin >> n >> a >> b;
    cout << bin_search(n, a, b);
}