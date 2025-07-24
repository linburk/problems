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
bool comp(int a, int b){
    return a > b;
}
void solve(){
    vector<int> people;
    vector<int> tarifs;
    string peoples, tarifss;
    getline(cin, peoples);
    getline(cin, tarifss);
    peoples += " ";
    tarifss += " ";
    string numb;
    for (auto i : peoples){
        if (isnumber(i)){
            numb += i;
        }
        else {
            people.push_back(stoi(numb));
            numb = "";
        }
    }
    for (auto i : tarifss){
        if (isnumber(i)){
            numb += i;
        }
        else {
            tarifs.push_back(stoi(numb));
            numb = "";
        }
    }

    sort(all(people), comp);
    sort(all(tarifs));
    ll ans = 0;
    for (int i = 0; i < len(people); i++){
        ans += people[i] * tarifs[i];
    }
    cout << ans;
}
int32_t main() {
    $FASTSTREAM
    solve();
}