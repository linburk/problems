#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;
using i64 = long long;

int main()
{
#if __APPLE__
    std::freopen(std::getenv("FINPATH"), "r", stdin);
    std::freopen(std::getenv("FOUTPATH"), "w", stdout);
#else
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
#endif
    string n;
    i64 k;
    cin >> n >> k;
    vector<vector<unordered_map<i64, i64>>> dp(n.size(), vector<unordered_map<i64, i64>>(2));
    for (int i = 1; i < 10; ++i) {
        if (i < n[0] - '0') {
            dp[0][0][i] = 1;
        } else if (i == n[0] - '0') {
            dp[0][1][i] = 1;
        }
    }
    for (int i = 1; i < n.size(); ++i) {
        for (int j = 0; j < 10; ++j) {
            if (j > 0) {
                dp[i][0][j] += 1;
            }
            for (auto& [mult, count] : dp[i - 1][0]) {
                dp[i][0][mult * j] += count;
            }
            if (j == n[i] - '0') {
                for (auto& [mult, count] : dp[i - 1][1]) {
                    dp[i][1][mult * j] += count;
                }
            }
            if (j < n[i] - '0') {
                for (auto& [mult, count] : dp[i - 1][1]) {
                    dp[i][0][mult * j] += count;
                }
            }
        }
    }
    i64 res = 0;
    for (auto& [mult, count] : dp.back()[0])
        if (mult <= k)
            res += count;
    for (auto& [mult, count] : dp.back()[1])
        if (mult <= k)
            res += count;
    cout << res << '\n';
}
