#include <iostream>
#include <algorithm>

using namespace std;

int main(){
    
    int K, T;
    cin >> K >> T;

    int x, n; 
    n = T / K;
    x = abs(K * (n % 2) - T % K);
    
    cout << x;
}