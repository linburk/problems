#include <queue>
#include <deque>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <stack>
#include <list>
using namespace std;

int main(){
    int r;
    cin >> r;
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    sort(a.begin(), a.end());
    int cnt = 0;
    int last = r - 3;
    for (int i = 0; i < n; i++){
        if (a[i] >= last + 3) {
            last = a[i];
            cnt++;
        }
    }
    cout << cnt;
}