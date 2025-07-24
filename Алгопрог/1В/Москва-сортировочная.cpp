#include <iostream>
#include <vector>
using namespace std;
int main(){
    int n, cnt = 0;
    cin >> n;
    vector<int> a(n);
    for (int i = 0 ; i < n ; i++){
        cin >> a[i];
    }
    for (int i = n - 1 ; i >= 0 ; i--){
        if (a[i] < a[n - i - 1]){
            int c;
            c = a[i];
            a[i] = a[n - i - 1];
            a[n - i -  1] = c;
            cnt++;
        }
    }
    cout << cnt;
}