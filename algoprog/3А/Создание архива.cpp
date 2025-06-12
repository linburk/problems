#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    int s, n;
    cin >> s >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    sort(a.begin(), a.end());
    int sum = 0;
    int cnt = -1;
    while (sum <= s and cnt < n) {
        cnt++;
        sum += a[cnt];
        
    }
    cout << cnt;
}