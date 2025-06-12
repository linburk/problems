#include <stdio.h>
#include <algorithm>
#include <bitset>
#include <cmath>
#include <deque>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

#define endl '\n'
#define all(cont) cont.begin(), cont.end()
#define unique(cont) cont.erase(unique(all(cont)), cont.end())
#define pb(x) emplace_back(x)

namespace tools {

    template <typename T>
    T gcd(T a, T b) {
        while (b > 0) {
            a %= b;
            std::swap(a, b);
        }
        return a;
    }

    template <typename T>
    T lcm(T a, T b) {
        return a * b / gcd(a, b);
    }

    template <typename T>
    std::istream &operator>>(std::istream &is, std::vector<T> &array) {
        for (auto &i : array) {
            is >> i;
        }
        return is;
    }

    template <typename T>
    std::ostream &operator<<(std::ostream &os, const std::vector<T> &array) {
        for (const auto &i : array) {
            os << i << " ";
        }
        return os;
    }

    template <typename T>
    std::istream &operator>>(std::istream &is,
                             std::vector<std::vector<T> > &matrix) {
        for (auto &i : matrix)
            for (auto &j : i) is >> j;
        return is;
    }

    template <typename T>
    std::ostream &operator<<(std::ostream &os,
                             const std::vector<std::vector<T> > &matrix) {
        for (const auto &i : matrix) {
            for (const auto &j : i) os << j << " ";
            os << "\n";
        }
        return os;
    }

    template <typename T, typename V>
    std::istream &operator>>(std::istream &is, std::pair<T, V> &p) {
        is >> p.first >> p.second;
        return is;
    }

}  // namespace tools
using namespace tools;

vector<int> pows;
ll h(deque<char> s){
    ll res = 0;
    for (int i = 0; i < s.size(); i++){
        res += (s[i] - 'a' + 1) * pows[i];
    }
    return res;
}
void solve() {
    string a, b;
    getline(cin, a);
    getline(cin, b);
    pows.resize(max(a.size(), b.size()));
    pows[0] = 1;
    for (int i = 1; i < a.size(); i++){
        pows[i] = pows[i - 1] * 31;
    }
    vector<ll> hash(a.size());
    deque<char> temp;
    for (auto i : a)
        temp.push_back(i);
    for (int i = 0; i < a.size(); i++){
        hash[i] = h(temp);
        temp.push_front(temp.back());
        temp.pop_back();
    }
    temp.clear();
    for (auto i : b)
        temp.push_back(i);
    ll search = h(temp);
    for (int i = 0; i < a.size(); i++){
        if (hash[i] == search) {
            cout << i << " ";
            exit(0);
        }
    }
    cout << -1;
}

int32_t main() {
    setlocale(LC_ALL, "Russian");
#ifdef __APPLE__
    std::freopen("input.txt", "r", stdin);
    std::freopen("output.txt", "w", stdout);
#endif
    std::cin.tie(0);
    std::cout.tie(0);
    std::ios_base::sync_with_stdio(false);
//    int t;
//    cin >> t;
//    for (int i = 0; i < t; i++)
    solve();
    return 0;
}