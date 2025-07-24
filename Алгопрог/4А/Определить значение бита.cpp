#include <iostream>
using namespace std;

int main(){
    long long n, i;
    cin >> n >> i;
    long long mask = (1 << (i - 1));
    if (n & mask)
        cout << 1;
    else
        cout << 0;
}