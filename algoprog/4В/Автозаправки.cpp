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
#define $FASTSTREAM std::cin.tie(nullptr); std::cout.tie(nullptr); std::ios_base::sync_with_stdio(false);
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
    vector<pair<ll, int> > zapr(n);
    for (int i = 0; i < n; i++){
        cin >> zapr[i].first;
        zapr[i].second = i + 1;
    }
    sort(all(zapr));
    ll mins = 1e10, mini = -1;
    for (int i = 1; i < n; i++){
        if (zapr[i].first - zapr[i - 1].first < mins){
            mins = zapr[i].first - zapr[i - 1].first;
            mini = zapr[i].second;
        }
    }
    cout << mini;
}
int32_t main() {
    $FASTSTREAM
    solve();
}