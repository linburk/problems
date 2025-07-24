#include <queue>
#include <deque>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <stack>
#include <list>

using namespace std;

bool check(vector<int> &st, int k, int rast){
    int can = 1;
    int last = st[0];
    for (auto i : st){
        if (i - last >= rast){
            can++;
            last = i;
        }
    }
    if (can >= k)
        return 1;
    else
        return 0;
}

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> st(n);
    for (int i = 0; i < n; i++)
        cin >> st[i];
    sort(st.begin(), st.end());
    int l = 0, r = 100000;
    while (r - l > 1){
        int m = (r + l) / 2;
        if (check(st, k, m)){
            l = m;
        }
        else
            r = m;
    }
    cout << l;
}