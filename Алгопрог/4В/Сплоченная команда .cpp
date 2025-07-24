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
bool comp(pair<int, int> a, pair<int, int> b){
    return a.first > b.first;
}
void solve(){
    int n;
    cin >> n;
    vector<pair<int, int> > people(n);
    for (int i = 0; i < n; i++){
        cin >> people[i].first;
        people[i].second = i + 1;
    }
    sort(all(people), comp);
    ll i = 0, j = 0;
    ll cur = 0, max = -1;
    deque<int> curs, maxs;
    while (i < n - 1 and j < n){
        while (i + 1 != j and j != i and people[i + 1].first + people[j].first < people[i].first){
            cur -= people[i].first;
            curs.pop_front();
            i++;
        }
        cur += people[j].first;
        curs.push_back(people[j].second);
        j++;
        if (cur > max){
            max = cur;
            maxs = curs;
        }
    }
    cout << len(maxs) << " " << max << endl;
    for (auto k : maxs){
        cout << k << endl;
    }
}
int32_t main() {
    $FASTSTREAM
    solve();
}