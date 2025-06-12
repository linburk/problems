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
struct triple{
    ll left;
    ll right;
    ll value;
};
bool check(ll &middle, vector<triple> &apref, ll r){
    ll cnt = 0;
    map<int, bool> used;
    for (auto i : apref){
        if (i.value <= middle and !(used[i.left] or used[i.right])){
            for (int j = i.left; j <= i.right; j++) {
                used[j] = 1;
            }
            cnt++;
        }
    }
    if (cnt >= r)
        return 1;
    return 0;
}
void solve(){
    ll n, r, c;
    cin >> n >> r >> c;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++){
        cin >> a[i];
    }
    sort(all(a));
//    for (auto i : a){
//        cout << i << " ";
//    }
//    cout << endl;
    vector<triple> apref;
    for (int i = c - 1; i < n; i++){
        triple t;
        t.left = i - c + 1;
        t.right = i;
        t.value = a[i] - a[i - c + 1];
        apref.push_back(t);
    }
//    for (auto i : apref)
//        cout << i.value << " " << i.left << " " << i.right << endl;
    ll left = 0, right = 1e10;
    while (right - left > 1){
        ll middle = (right + left) / 2;
        if (check(middle, apref, r)){
            right = middle;
        }
        else {
            left = middle;
        }
    }
    cout << right;
}
int32_t main() {
    $FASTSTREAM
    solve();
}