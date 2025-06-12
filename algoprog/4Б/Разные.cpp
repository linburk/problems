#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define INT_MIN -2000000000
int main(){
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    sort(a.begin(), a.end());
    int last = INT_MIN, cnt = 0;
    for (auto i : a){
        if (i != last){
            cnt++;
            last = i;
        }
    }
    cout << cnt;
}