#include <algorithm>
#include <deque>
#include <functional>
#include <iostream>
#include <vector>

using std::cin, std::cout;
using std::vector, std::deque, std::pair;

int main()
{
    cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
#ifdef __APPLE__
    std::freopen(std::getenv("FINPATH"), "r", stdin);
    std::freopen(std::getenv("FOUTPATH"), "w", stdout);
#endif
    int k;
    cin >> k;
    vector<vector<int>> a(k);
    for (int i = 0; i < k; ++i) {
        int len;
        cin >> len;
        a[i].resize(len);
        for (auto&& j : a[i])
            cin >> j;
    }
    int r = 0;
    vector<vector<vector<int>>> f;
    for (int i = 0; i < k; ++i) {
        vector<int> used(a[i].size() + 1);
        vector<vector<int>> dp(a[i].size(), vector<int>(a[i].size() + 1, -1));
        vector<int> val = a[i];
        std::sort(val.begin(), val.end());
        val.erase(std::unique(val.begin(), val.end()), val.end());
        int t = 1;
        std::function<int(int, int)> rec = [&](int l, int r) {
            if (dp[l][r] != -1)
                return dp[l][r];
            vector<int> g_to;
            for (int m = l; m < r; ++m) {
                vector<pair<int, int>> up;
                int m2 = l;
                while (m2 < r) {
                    if (a[i][m2] <= a[i][m]) {
                        ++m2;
                        continue;
                    }
                    int lt = m2;
                    while (m2 < a[i].size() && a[i][m2] > a[i][m])
                        ++m2;
                    int rt = m2;
                    up.push_back({ lt, rt });
                }
                int g = 0;
                for (auto [lt, rt] : up) {
                    rec(lt, rt);
                    g ^= dp[lt][rt];
                }
                g_to.push_back(g);
            }
            dp[l][r] = 0;
            for (int i = 0; i < g_to.size(); ++i)
                used[g_to[i]] = t;
            while (used[dp[l][r]] == t)
                ++dp[l][r];
            ++t;
            return dp[l][r];
        };
        rec(0, a[i].size());
        f.push_back(std::move(dp));
        r ^= f[i][0][a[i].size()];
    }
    cout << (r ? "G" : "S") << "\n";
    if (r) {
        for (int i = 0; i < k; ++i) {
            r ^= f[i][0][a[i].size()];
            for (int j = 0; j < a[i].size(); ++j) {
                vector<pair<int, int>> up;
                int m = 0;
                while (m < a[i].size()) {
                    if (a[i][m] <= a[i][j]) {
                        ++m;
                        continue;
                    }
                    int lt = m;
                    while (m < a[i].size() && a[i][m] > a[i][j])
                        ++m;
                    int rt = m;
                    up.push_back({ lt, rt });
                }
                int g = 0;
                for (auto [lt, rt] : up)
                    g ^= f[i][lt][rt];
                if ((g ^ r) == 0) {
                    cout << i + 1 << " " << j + 1 << "\n";
                    return 0;
                }
            }
            r ^= f[i][0][a[i].size()];
        }
    }
}
