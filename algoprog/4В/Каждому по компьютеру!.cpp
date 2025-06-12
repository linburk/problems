#include <queue>
#include <deque>
#include <iostream>
#include <set>
#include <algorithm>
#include <string>
#include <cmath>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <stack>
#include <list>
#include <iterator>
#include <iomanip>
#include <stdio.h>
#include <bitset>
using namespace std;
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
#define endl '\n'
#define all(cont) cont.begin(), cont.end()
#define len(cont) cont.size()
#define $FASTSTREAM \
    std::cin.tie(nullptr); \
    std::cout.tie(nullptr); \
    std::ios_base::sync_with_stdio(false);
ll gcd(ll a, ll b) {
    while (b > 0) {
        a %= b;
        swap(a, b);
    }
    return a;
}
ll lcm(ll a, ll b) {
    return a * b / gcd(a, b);
}
ll max(ll a, ll b) {
    if (a > b)
        return a;
    return b;
}
ll min(ll a, ll b) {
    if (a < b)
        return a;
    return b;
}

void solve(){
    int n, m;
    cin >> n >> m;
    vector<int>  groups(n);
    vector<pair<int, int> > computers(m);
    for (int i = 0; i < n; i++){
        cin >> groups[i];
    }
    for (int i = 0; i < m ; i++){
        cin >> computers[i].first;
        computers[i].first--;
        computers[i].second = i + 1;
    }
    sort(all(computers));
    vector<int> ans(m, 0);
    int cnt = 0;
    for (int i = 0; i < n; i++){
        auto it = lower_bound(all(computers), make_pair(groups[i], 0));
        if (it != computers.end() and ans[distance(computers.begin(), it)] == 0){
            ans[distance(computers.begin(), it)] = it->second;
            cnt++;
        }
    }
    cout << cnt << endl;
    for (auto i : ans)
        cout << i << " ";
}
int32_t main() {
    $FASTSTREAM
    solve();
}