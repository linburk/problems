#include <iostream>
using namespace std;

int main(){
    int n;
    cin >> n;
    int a[1001] = {0};
    a[0] = 1;
    a[1] = 1;
    for (int i = 2; i <= n; i++){
        if (i % 2 == 0){
            a[i] = a[i / 2] + a[i / 2 - 1];
        }
        else {
            a[i] = a[i / 2 + 1] - a[i / 2]; 
        }
    }
    cout << a[n];
}