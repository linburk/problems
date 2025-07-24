#include <queue>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
using namespace std;

int bin(vector<int> &a, int b){
    bool flag = false;
    int l = 0, r = a.size() - 1;
    while (r - l > 1){
        int m = (l + r) / 2;
        if (a[m] < b){
            l = m;
        }
        else
            r = m;
    }
    if (a[r] == b){
        flag = true;
    }
    if (b - a[l] <= a[r] - b)
        return a[l];
    else
        return a[r];
}

int main(){
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    for (int i = 0; i < m; i++){
        cin >> b[i];
    }
    for (auto i : b){
        cout << bin(a, i) << endl;
    }
}