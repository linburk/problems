#include <algorithm>
#include <array>
#include <deque>
#include <functional>
#include <iostream>
#include <vector>

using std::cin, std::cout;
using std::vector, std::array, std::deque, std::pair;

int main()
{
    cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
#ifdef __APPLE__
    std::freopen(std::getenv("FINPATH"), "r", stdin);
    std::freopen(std::getenv("FOUTPATH"), "w", stdout);
#endif
    int n, m;
    cin >> n >> m;
    vector<vector<array<int, 2>>> dp(n, vector<array<int, 2>>(m));
    dp[n - 1][m - 1] = { 0, 0 };
    for (int i = n - 1; i >= 0; --i) {
        for (int j = m - 1; j >= 0; --j) {
            for (int p = 0; p < 2; ++p) {
                bool win = 0;
                for (int k = i + 1; k < n; ++k)
                    win |= !dp[k][j][p ^ 1];
                for (int k = j + 1; k < m; ++k)
                    win |= !dp[i][k][p ^ 1];
                for (int k = 1; k < std::min(n - i, m - j); ++k)
                    win |= !dp[i + k][j + k][p ^ 1];
                dp[i][j][p] = win;
            }
        }
    }
    cout << (dp[0][0][0] ^ 1) + 1 << "\n";
}
