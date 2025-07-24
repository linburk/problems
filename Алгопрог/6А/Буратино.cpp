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

void solve() {
    uint n;
    cin >> n;
    vector<pair<uint, uint> > clock;
    for (int i = 0; i < n; i++){
        uint HH, MM, SS, sec;
        char c;
        cin >> HH >> c >> MM >> c >> SS >> sec;
        clock.push_back({(HH - 9) * 60 * 60 + MM * 60 + SS, sec});
    }
    clock.push_back({9 * 60 * 60 + 1, 0});
    vector<uint> dp(9 * 60 * 60 + 1, 0);
    vector<uint> time(9 * 60 * 60 + 1);
    for (int i = 0; i < clock.size() - 1; i++){
        for (int j = clock[i].first; j < clock[i + 1].first; j++)
            time[j] = clock[i].second;
    }
    for (int i = 0; i < 9 * 60 * 60; i++){
        if ((i + time[i] <= 4 * 60 * 60 or i >= 5 * 60 * 60) and i + time[i] <= 9 * 60 * 60)
            dp[i + time[i]] = max(dp[i + time[i]], dp[i] + 1);
        dp[i + 1] = max(dp[i + 1], dp[i]);

    }
//    for (int i = 0; i < 9; i++){
//        for (int j = i * 60 * 60; j < (i + 1) * 60 * 60; j++)
//            cout << dp[j] << " ";
//        cout << endl;
//    }
    cout << dp[9 * 60 * 60];
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