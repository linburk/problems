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
    int n;
    cin >> n;
    int f = 0;
    vector<vector<int>> g(101, vector<int>(101));
    vector<int> used(300);
    for (int i = 1, t = 1; i <= 100; ++i) {
        for (int j = 1; j <= 100; ++j, ++t) {
            if (i == j)
                continue;
            for (int k = 1; k <= i; ++k)
                if (i - k != 0 && i - k != j)
                    used[g[i - k][j]] = t;
            for (int k = 1; k <= j; ++k)
                if (j - k != 0 && j - k != i)
                    used[g[i][j - k]] = t;
            for (int k = 1; k <= std::min(i, j); ++k)
                if (i - k != 0 && j - k != 0)
                    used[g[i - k][j - k]] = t;
            while (used[g[i][j]] == t)
                ++g[i][j];
        }
    }
    for (int i = 0; i < n; ++i) {
        int l, c;
        cin >> l >> c;
        if (l == 0 || c == 0 || l == c)
            f = -1;
        f ^= g[l][c];
    }
    cout << (f ? "Y" : "N") << "\n";
}
