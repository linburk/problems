#include <bits/stdc++.h>
using namespace std;

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

#define endl '\n'
#define all(cont) cont.begin(), cont.end()
#define funique(cont) cont.erase(unique(all(cont)), cont.end())

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

void solve(){
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<vector<int> > dp(s.size() + 1, vector<int>(n + 1, 0));
    dp[0][0] = 1;
    vector<int> touches(1);
    for (auto i : s){
        if (i == 'A' or i == 'B' or i == 'C') touches.push_back(1);
        if (i == 'D' or i == 'E' or i == 'F') touches.push_back(2);
        if (i == 'G' or i == 'H' or i == 'I') touches.push_back(3);
        if (i == 'J' or i == 'K' or i == 'L') touches.push_back(4);
        if (i == 'M' or i == 'N' or i == 'O') touches.push_back(5);
        if (i == 'P' or i == 'Q' or i == 'R' or i == 'S') touches.push_back(6);
        if (i == 'T' or i == 'U' or i == 'V') touches.push_back(7);
        if (i == 'W' or i == 'X' or i == 'Y' or i == 'Z') touches.push_back(8);
    }    
    for (int i = 1; i <= s.size(); i++){
        for (int j = 1; j <= n; j++){
            if (i >= 4 && (touches[i] == 6 || touches[i] == 8)){
                if (touches[i] == touches[i - 1] && touches[i - 1] == touches[i - 2] && touches[i - 2] == touches[i - 3]){
                    dp[i][j] += dp[i - 4][j - 1];
                }
            }
            if (i >= 3){
                if (touches[i] == touches[i - 1] && touches[i - 1] == touches[i - 2]){
                    dp[i][j] += dp[i - 3][j - 1];
                }
            }
             if (i >= 2){
                if (touches[i] == touches[i - 1]){
                    dp[i][j] += dp[i - 2][j - 1];
                }
            }
            dp[i][j] += dp[i - 1][j - 1];
        }
    }
    cout << dp[s.size()][n];
}

int32_t main() {
    setlocale(LC_ALL, "Russian");
#ifdef __APPLE__
    std::freopen("/Users/dmitrii/Documents/Code/Code/input.txt", "r", stdin);
    std::freopen("/Users/dmitrii/Documents/Code/Code/output.txt", "w", stdout);
#endif
    std::cin.tie(0);
    std::ios_base::sync_with_stdio(false);
//    int t;
//    cin >> t;
//    for (int i = 0; i < t; i++)
    solve();
    return 0;
}