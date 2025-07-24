#include <algorithm>
#include <array>
#include <cassert>
#include <functional>
#include <iostream>
#include <vector>
#include <deque>

using std::cin, std::cout;
using std::vector, std::array, std::deque, std::pair;

int const mod = 1E9 + 7;

using i64 = long long;
template <typename T> using matrix = vector<vector<T> > ;
template <typename T> matrix<T> operator*(matrix<T> a, matrix<T> b) {
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
matrix<T> pow(matrix<T> a, i64 k) {
    matrix<T> rs(a.size(), vector<T>(a.size()));
    for (int i = 0; i < rs.size(); ++i)
        rs[i][i] = 1;
    for (; k; k >>= 1) {
        if (k & 1) rs = rs * a;
        a = a * a;
    }
    return rs;
}

int main() {
    cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
#ifdef __APPLE__
    std::freopen(std::getenv("FINPATH"), "r", stdin);
    std::freopen(std::getenv("FOUTPATH"), "w", stdout);
#endif
    int a, b, c, d, e;
    i64 n;
    cin >> a >> b >> c >> d >> e >> n;
    if (n <= 2) {
        cout << "1\n";
        return 0;
    }
    matrix<int> dp(5);
    dp[0] = {a, b, c, d, e}; // f i
    dp[1] = {1, 0, 0, 0, 0}; // f i-1
    dp[2] = {0, 0, 2, 0, 0}; // 2^i
    dp[3] = {0, 0, 0, 1, 1}; // i
    dp[4] = {0, 0, 0, 0, 1}; // 1
    dp = pow(dp, n - 2);
    dp = dp * matrix<int>{{1}, {1}, {8}, {3}, {1}};
    cout << dp[0][0] << "\n";
}

