#include <iostream>
using namespace std;

int main(){
    long long n;
    cin >> n;
    unsigned long long ans = 1 << (n - 1);
    cout << ans;
}