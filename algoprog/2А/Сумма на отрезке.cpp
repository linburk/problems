#include <iostream>
#include <algorithm>
using namespace std;

int main(){
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    vector<int> sum(n + 1, 0);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++){
        sum[i] = sum[i - 1] + a[i - 1];
    }
    int l, r;
    for (int i = 0; i < m; i++){
        cin >> l >> r;
        cout << sum[r] - sum[l - 1] << endl;
    }
}