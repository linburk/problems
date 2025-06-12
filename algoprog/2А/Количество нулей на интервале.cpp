#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> pref(n + 1);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    for (int i = 1, cnt = 0; i <= n; i++){
        if (a[i - 1] == 0)
            cnt++;
        pref[i] = cnt;
    }
    int k;
    cin >> k;
    int l, r;
    for (int i = 0; i < k; i++){
        cin >> l >> r;
        cout << pref[r] - pref[l - 1] << " ";
    }
}