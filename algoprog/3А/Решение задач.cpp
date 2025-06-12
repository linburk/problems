#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    int start, n;
    cin >> n >> start;
    vector<pair<int, int> > a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i].first >> a[i].second;
    }
    int cnt = 0;
    sort(a.begin(), a.end());
    for (int i = 0; i < n; i++){
        if (a[i].first > start)
            break;
        start += a[i].second;
        cnt++;
    }
    cout << cnt;
}