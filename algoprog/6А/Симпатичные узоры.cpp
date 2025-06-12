#include <stdio.h>
#include <algorithm>
#include <bitset>
#include <cmath>
#include <deque>
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

#ifdef __APPLE__
#include <fstream>
std::ifstream input("input.txt");
std::ofstream output("output.txt");
#define cin input
#define cout output
#endif

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

    template <typename T>
    std::istream &operator>>(std::istream &is, std::pair<T, T> &p) {
        is >> p.first >> p.second;
        return is;
    }

}  // namespace tools
using namespace tools;

bool check(bitset<32> a, bitset<32> b, int m){
    for (int i = 1; i < m; i++){
        if ((a[i] == a[i - 1]) and (a[i - 1] == b[i]) and (b[i] == b[i - 1])){
            return 0;
        }
    }
    return 1;
}


void solve() {
    int n, m;
    cin >> n >> m;
    if (m > n)
        swap(n, m);
    vector<vector<bool> > pr(1 << m, vector<bool>(1 << m));
    for (int i = 0; i < (1 << m); i++){
        for (int j = 0; j < (1 << m); j++){
            pr[i][j] = check(bitset<32>(i), bitset<32>(j), m);
        }
    }
    vector<vector<int> > dp(n, vector<int>((1 << m), 0));
    for (int j = 0; j < (1 << m); j++){
        dp[0][j] = 1;
    }
    for (int i = 1; i < n; i++){
        for (int j = 0; j < (1 << m); j++){
            for (int k = 0; k < (1 << m); k++){
                dp[i][j] += pr[k][j] * dp[i - 1][k];
            }
        }
    }
    ll sum = 0;
    for (int j = 0; j < (1 << m); j++){
        sum += dp[n - 1][j];
    }
    cout << sum;
}

int32_t main() {
    setlocale(LC_ALL, "Russian");
#ifndef __APPLE__
    std::cin.tie(0);
    std::cout.tie(0);
    std::ios_base::sync_with_stdio(false);
#endif
//    int t;
//    cin >> t;
//    for (int i = 0; i < t; i++)
    solve();
    return 0;
}