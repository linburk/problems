#include <iostream>
#include <vector>

using i64 = long long;
using std::vector;

int main()
{
    int const mod = 1E9 + 7;
    int n;
    std::cin >> n;
    vector<i64> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    vector<i64> pref(n + 1);
    for (int i = 0; i < n; ++i) {
        pref[i + 1] = pref[i] + a[i];
    }
    vector<vector<int>> dp(n + 1, vector<int>(n + 1));
    dp[0][0] = 1;
    for (int j = 1; j <= n; ++j) {
        std::vector<int> cnt_mod(j);
        for (int i = 1; i <= n; ++i) {
            cnt_mod[pref[i - 1] % j] = (cnt_mod[pref[i - 1] % j] + dp[i - 1][j - 1]) % mod;
            dp[i][j] = (dp[i][j] + cnt_mod[pref[i] % j]) % mod;
        }
    }
    int res = 0;
    for (int j = 1; j <= n; ++j) {
        res = (res + dp[n][j]) % mod;
    }
    std::cout << res << '\n';
}
