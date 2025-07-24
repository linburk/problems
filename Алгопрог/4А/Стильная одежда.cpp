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
    int n, m;
    cin >> n;
    vector<int> s(n);
    for (int i = 0; i < n; i++)
        cin >> s[i];
    cin >> m;
    vector<int> t(m);
    for (int i = 0; i < m; i++)
        cin >> t[i];
    int i = 0, j = 0, min = 1e9;
    pair<int, int> mem;
    while (i < n and j < m){
        if (abs(s[i] - t[j]) < min) {
            min = abs(s[i] - t[j]);
            mem.first = s[i];
            mem.second = t[j];
        }
        if (s[i] < t[j])
            i++;
        else
            j++;
    }
    cout << mem.first << " " << mem.second;
}