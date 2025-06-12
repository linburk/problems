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
bool comp(char a, char b){
    if (a == '0')
        return 1;
    if (b == '0')
        return 0;
    return a < b;
}
void solve(string s){
    for (int i = 0; i < len(s); i++){
        if ((int)s[i] < (int)s[0] and s[i] != '0' or s[0] == '0'){
            swap(s[i], s[0]);
        }
    }
    sort(s.begin() + 1, s.end(), comp);
    for (auto i : s)
        cout << i;
}
int32_t main() {
    $FASTSTREAM
    string s;
    getline(cin, s);
    solve(s);
}