#include <algorithm>
#include <array>
#include <cassert>
#include <deque>
#include <functional>
#include <iostream>
#include <vector>

using std::cin, std::cout;
using std::vector, std::array, std::deque, std::pair;

using i64 = long long;

int main()
{
    cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
#ifdef __APPLE__
    std::freopen(std::getenv("FINPATH"), "r", stdin);
    std::freopen(std::getenv("FOUTPATH"), "w", stdout);
#endif
    int n, m, s;
    cin >> n >> m >> s;
    vector<vector<int>> g(n + 1, vector<int>(m + 1));
    vector<int> used(n * m);
    for (int i = 1, t = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j, ++t) {
            if (i == 1 && j <= s || j == 1 && i <= s)
                continue;
            for (int m = 1; m < i; ++m)
                used[g[m][j] ^ g[i - m][j]] = t;
            for (int m = 1; m < j; ++m)
                used[g[i][m] ^ g[i][j - m]] = t;
            while (used[g[i][j]] == t)
                ++g[i][j];
        }
    }
    cout << (g[n][m] ? "1\n" : "2\n");
}
