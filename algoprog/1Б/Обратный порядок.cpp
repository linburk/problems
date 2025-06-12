#include <iostream>
using namespace std;
int main(){
    int n;
    cin >> n;
    int a[100000];
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    for (int i = 0; i < n/2; i++){
        a[i] = a[i] + a[n-i-1]; 
        a[n-i-1] = a[i] - a[n-i-1];
        a[i] = a[i] - a[n-i-1];
    }
    for (int i = 0; i < n; i++){
        cout << a[i] << " ";
    }
}