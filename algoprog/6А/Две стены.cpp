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

void solve() {
    const size_t MAXK = 101;
    int n, k;
    cin >> n >> k;
    vector<vector<pair<int, int> > > bricks(k + 1, vector<pair<int, int> >(1, {0, 0}));
    ll sum = 0;
    for (int i = 0; i < n; i++){
        int l, c;
        cin >> l >> c;
        bricks[c].push_back({l, i + 1});
    }
    for (int i = 0; i < bricks[1].size(); i++)
        sum += bricks[1][i].first;
    vector<vector<vector<bool > > > dp(k + 1);
    for (int i = 0; i <= k; i++) {
        dp[i].resize(bricks[i].size(), vector<bool>(sum + 1, 0));
    }
    for (int i = 1; i <= k; i++)
        dp[i][0][0] = dp[i][1][0] = dp[i][1][bricks[i][1].first] = 1;
    for (int i = 1; i <= k; i++){
        for (int j = 2; j < bricks[i].size(); j++){
            for (int m = 0; m <= sum; m++){
                dp[i][j][m] = dp[i][j - 1][m] || bricks[i][j].first <= m && dp[i][j - 1][m - bricks[i][j].first];
            }
        }
    }
    bitset<MAXK> checker;
    for (int m = 1; m < sum / 2 + 1; m++){
        checker.reset();
        for (int i = 1; i <= k; i++) {
            for (int j = 1; j < bricks[i].size(); j++) {
                checker[i] = checker[i] | dp[i][j][m];
            }
        }
        int i = 1;
        for (i = 1; i < k; i++) {
            if (!checker[i]) {
                break;
            }
        }
        if (!checker[i])
            continue;

        cout << "YES" << endl;
        for (i = 1; i <= k; i++){
            int st = m;
            for (int j = bricks[i].size() - 1; j >= 0 && st > 0; j--){
                if (dp[i][j][st] != dp[i][j - 1][st]) {
                    cout << bricks[i][j].second << " ";
                    st -= bricks[i][j].first;
                }
            }
        }
        exit(0);
    }
    cout << "NO";
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