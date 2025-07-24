#include <iostream>

using namespace std;

int main(){
    int n, m, k;
    cin >> n >> m >> k;
    int a = m / 2;
    int b = k * a - m;
    if (b >= n)
        cout << a;
    else 
        cout << 0;
}