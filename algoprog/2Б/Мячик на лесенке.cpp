#include <iostream>
using namespace std;

int main(){
    int n;
    cin >> n;
    int a[31];
    a[0] = 1;
    a[1] = 1;
    a[2] = 2;
    for (int i = 3; i <= n; i++){
        a[i] = a[i - 1] + a[i - 2] + a[i - 3];
    }
    cout << a[n];
}