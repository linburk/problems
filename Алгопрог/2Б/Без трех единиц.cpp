#include <iostream>
#include <cmath>
using namespace std;

int main(){
    int n;
    cin >> n;
    int cur = 0;
    for (int i = 3, last = 0; i <= n; i++){
        cur = last * 2 + 1;
        last = cur;
    }
    cout << pow(2, n) - cur;
}