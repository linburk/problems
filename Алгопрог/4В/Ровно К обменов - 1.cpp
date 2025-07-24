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
void bubble(vector<int> &a, ll k){
    ll cnt = 0;
    for (int i = 0; i < len(a); i++){
        if (cnt == k)
            break;
        for (int j = 1; j < len(a) - i; j++){
            if (cnt == k)
                break;
            if (a[j - 1] < a[j]){
                swap(a[j - 1], a[j]);
                cnt++;
            }
        }
    }
}

void solve(){
    ll n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 1; i <= n; i++){
        a[i - 1] = i;
    }
    bubble(a, k);
//    cout << bubble_s(a) << endl;
    for (auto i : a)
        cout << i << " ";
}
int32_t main() {
    $FASTSTREAM
    solve();
}