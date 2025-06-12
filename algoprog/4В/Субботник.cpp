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
    ll n, r, c;
    cin >> r >> c;
    n = r * c;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(all(a));
    ll max = -1;
    for (int i = c - 1; i < len(a); i += c){
        if (a[i] - a[i - c + 1] > max)
            max = a[i] - a[i - c + 1];
    }
    cout << max;
}
int32_t main() {
    $FASTSTREAM
    solve();
}