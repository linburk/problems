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
    int n;
    cin >> n;
    vector<int> classes(n);
    cin >> classes;
    vector<vector<ld> > dp(n, vector<ld>(101, 0));
    vector<vector<int> > past(n, vector<int>(101, -1));
    for (int i = 1; i < n; i++){
        for (int j = 1; j <= classes[i]; j++){
            for (int k = 1; k <= classes[i - 1]; k++){
                if (dp[i - 1][k] + (ld)j / k > dp[i][j]) {
                    dp[i][j] = dp[i - 1][k] + (ld) j / k;
                    past[i][j] = k;
                }
            }
        }
    }
    ld res = 0;
    int resi = -1;
    for (int j = 1; j <= classes[n - 1]; j++){
        if (dp[n - 1][j] > res) {
            res = max(res, dp[n - 1][j]);
            resi = j;
        }
    }
    vector<int> ans;
    for (int i = n - 1; i >= 0; i--){
        ans.push_back(resi);
        resi = past[i][resi];
    }
    cout << setprecision(6) << fixed << res << endl;
    for (int i = n - 1; i >= 0; i--){
        cout << ans[i] << " ";
    }
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