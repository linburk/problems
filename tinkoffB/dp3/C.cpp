#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <deque>
#include <functional>
#include <iostream>
#include <numeric>
#include <vector>

using std::cin, std::cout;
using std::vector, std::array, std::deque, std::pair;

int const mod = 1E9 + 7;

using i64 = long long;
template <typename T>
using matrix = vector<vector<T>>;
template <typename T>
matrix<T> operator*(matrix<T> a, matrix<T> b)
{
    matrix<T> rs(a.size(), vector<T>(b[0].size()));
    for (int i = 0; i < a.size(); ++i) {
        for (int j = 0; j < b[0].size(); ++j) {
            for (int k = 0; k < b.size(); ++k) {
                rs[i][j] = (1ll * a[i][k] * b[k][j] + rs[i][j]) % mod;
            }
        }
    }
    return rs;
};

template <typename T>
matrix<T> pow(matrix<T> a, i64 k)
{
    matrix<T> rs(a.size(), vector<T>(a.size()));
    for (int i = 0; i < rs.size(); ++i)
        rs[i][i] = 1;
    for (; k; k >>= 1) {
        if (k & 1)
            rs = rs * a;
        a = a * a;
    }
    return rs;
}

int main()
{
    cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
#ifdef __APPLE__
    std::freopen(std::getenv("FINPATH"), "r", stdin);
    std::freopen(std::getenv("FOUTPATH"), "w", stdout);
#endif
    i64 n;
    int m;
    cin >> n >> m;
    if (m == 2 || m == 3) {
        cout << "1\n";
        return 0;
    }
    vector<int> can;
    --m;
    can.push_back(0);
    std::function<void(int, int)> generate = [&](int ms, int i) {
        if (i > m)
            return;
        if (i == m) {
            ms ^= 1 << i;
            can.push_back(ms);
            return;
        }
        generate(ms | (1 << i + 2), i + 2);
        generate(ms | (1 << i + 3), i + 3);
    };
    generate(0, -1);
    matrix<int> dp(can.size(), vector<int>(can.size()));
    for (int i = 0; i < dp.size(); ++i) {
        for (int j = 0; j < dp.size(); ++j) {
            if ((can[i] & can[j]) == 0 && can[j] != 0) {
                dp[i][j] = 1;
            }
        }
    }
    dp = pow(dp, n);
    cout << std::accumulate(dp[0].begin(), dp[0].end(), 0ll) % mod << "\n";
}
