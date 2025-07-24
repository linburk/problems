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
#define $FASTSTREAM std::cin.tie(0); std::cout.tie(0); std::ios_base::sync_with_stdio(false);
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
    ll n;
    cin >> n;
    vector<pair<int, int> > homies(n);
    for (int i = 0; i < n; i++){
        cin >> homies[i].first;
        homies[i].second = i;
    }
    ll m;
    cin >> m;
    vector<pair<int, int> > bombs(m);
    for (int i = 0; i < m; i++) {
        cin >> bombs[i].first;
        bombs[i].second = i + 1;
    }
    sort(all(bombs));
    sort(all(homies));
    vector<int> ans(n);
    int i = 0, j = 1;
    while (i < n){
        if (bombs[j].first <= homies[i].first and j < m - 1)
            j++;
        if (bombs[j].first - homies[i].first < homies[i].first - bombs[j - 1].first){
            ans[homies[i].second] = bombs[j].second;
        }
        else
            ans[homies[i].second] = bombs[j - 1].second;
        i++;
    }
    for (auto k : ans)
        cout << k << " ";
}
int32_t main() {
    $FASTSTREAM
    solve();
}