#include <iostream>
using namespace std;

int main(){
    int n;
    cin >> n;
    int a[21];
    a[0] = 1;
    a[1] = 3;
    for (int i = 2; i <= n; i++){
        a[i] = (a[i - 1] + a[i - 2]) * 2;
    }
    cout << a[n];
}