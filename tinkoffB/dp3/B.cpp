#include <algorithm>
#include <array>
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

struct st {
    struct nd {
        matrix<int> dp = {
            { 1, 0, 0 },
            { 0, 1, 0 },
            { 0, 0, 1 }
        };
    };
    vector<nd> tr;
    int sz;
    void build(int l, int r, int n)
    {
        if (l == r - 1) {
            if (l == 0) {
                tr[n].dp = { { 0 },
                    { 0 },
                    { 1 } };
            } else {
                tr[n].dp = {
                    { 0, 1, 0 },
                    { 0, 0, 1 },
                    { 1, 1, 1 }
                };
            }
            return;
        }
        int m = (l + r) >> 1;
        build(l, m, n << 1);
        build(m, r, n << 1 | 1);
        tr[n].dp = tr[n << 1 | 1].dp * tr[n << 1].dp;
    }
    void update(int i, int l, int r, int n)
    {
        if (l == r - 1) {
            for (int j = 0; j < 3; ++j)
                tr[n].dp[2][j] ^= 1;
            return;
        }
        int m = (l + r) >> 1;
        if (i < m)
            update(i, l, m, n << 1);
        else
            update(i, m, r, n << 1 | 1);
        tr[n].dp = tr[n << 1 | 1].dp * tr[n << 1].dp;
    }
    st(int n)
    {
        sz = n;
        tr.resize(4 * sz);
        build(0, sz, 1);
    }
    void update(int i)
    {
        update(i, 0, sz, 1);
    }
    int get()
    {
        return tr[1].dp[2][0];
    }
};

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
    st tr(n + 1);
    cout << tr.get() << "\n";
    for (int i = 0; i < m; ++i) {
        int x;
        cin >> x;
        tr.update(x);
        cout << tr.get() << "\n";
    }
}
