#include <bits/stdc++.h>
using namespace std;
 
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
 
#define all(cont) cont.begin(), cont.end()
#define funique(cont) cont.erase(unique(all(cont)), cont.end())
 
namespace tools {
mt19937_64 rng(chrono::steady_clock().now().time_since_epoch().count());
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
    template <typename T, typename V>
    std::istream &operator>>(std::istream &is, std::pair<T, V> &p) {
        is >> p.first >> p.second;
        return is;
    }
}  // namespace tools
 
using namespace tools;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    cin >> a;
    vector<vector<vector<int> > > dp(n, vector<vector<int> >(n, vector<int>(2, 0)));
    for (int i = 0; i < n; i++){
        dp[i][i][1] = a[i];
    }
    for (int k = 1; k < n; k++){
        for (int l = 0; l < n - k; l++){
            int r = l + k;
            if (dp[l + 1][r][0] + a[l] > dp[l][r - 1][0] + a[r]){
                dp[l][r][1] = dp[l + 1][r][0] + a[l];
                dp[l][r][0] = dp[l + 1][r][1];
            } else {
                dp[l][r][1] = dp[l][r - 1][0] + a[r];
                dp[l][r][0] = dp[l][r - 1][1];
            }
        }
    }
    cout << dp[0][n - 1][1];
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