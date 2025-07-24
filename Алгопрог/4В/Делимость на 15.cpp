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
    string s;
    getline(cin, s);
    ll ost3 = 0;
    for (int i = 0; i < len(s); i++){
        if (i % 2 == 0){
            ost3 += 1 * (s[i] == '1');
        }
        if (i % 2 == 1){
            ost3 += 2 * (s[i] == '1');
        }
    }
    if (ost3 % 3 != 0){
        cout << "NO";
        return;
    }
    ll ost5 = 0;
    for (int i = 0; i < len(s); i++){
        if (i % 4 == 0){
            ost5 += 1 * (s[i] == '1');
        }
        if (i % 4 == 1){
            ost5 += 2 * (s[i] == '1');
        }
        if (i % 4 == 2){
            ost5 += 4 * (s[i] == '1');
        }
        if (i % 4 == 3){
            ost5 += 3 * (s[i] == '1');
        }
    }
    if (ost5 % 5 != 0){
        cout << "NO";
        return;
    }
    cout << "YES";
}
int32_t main() {
    $FASTSTREAM
    solve();
}