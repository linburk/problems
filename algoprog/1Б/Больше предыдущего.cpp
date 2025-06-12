#include <iostream>
using namespace std;
int main(){
    int n, cnt, last;
    cnt = 0;
    cin >> n;
    last = 100000000;
    int a[100000];
    for (int i = 0; i < n; i++){
        cin >> a[i];
        if (a[i] > last) cnt++;
        last = a[i];
    }
    cout << cnt;
}