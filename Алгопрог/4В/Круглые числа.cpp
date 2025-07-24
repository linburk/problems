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
    int k;
    cin >> k;
    k--;
    int kt = k, bits = 0;
    while (kt > 0){
        kt >>= 1;
        bits++;
    }
    for (int j = max(0, bits - 1); j >= 0; j--){
        cout << (k & (1 << j) ? 5 : 0);
    }
}
int32_t main() {
    $FASTSTREAM
    solve();
}