#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

#define endl '\n'
#define all(cont) cont.begin(), cont.end()
#define unique(cont) cont.erase(unique(all(cont)), cont.end())
#define pb(x) emplace_back(x)

namespace tools {

    template <typename T>
    T gcd(T a, T b) {
        while (b > 0) {
            a %= b;
            std::swap(a, b);
        }
        return a;
    }

    template <typename T>
    T lcm(T a, T b) {
        return a * b / gcd(a, b);
    }

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

    template <typename T>
    std::istream &operator>>(std::istream &is,
                             std::vector<std::vector<T> > &matrix) {
        for (auto &i : matrix)
            for (auto &j : i) is >> j;
        return is;
    }

    template <typename T>
    std::ostream &operator<<(std::ostream &os,
                             const std::vector<std::vector<T> > &matrix) {
        for (const auto &i : matrix) {
            for (const auto &j : i) os << j << " ";
            os << "\n";
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


class sparseTable{
    vector<vector<ll> > ST;
    void build(const int first, const int size) {
        ST.resize(log2(size + 1) + 1, vector<ll>(size));
        ST[0][0] = first;
        for (int i = 1; i < size; i++){
            ST[0][i] = (23 * ST[0][i - 1] + 21563) % 16714589;
        }
        for (int i = 0; i + 1 < log2(size + 1); i++) {
            for (int j = 0; j < size - (1 << i); j++) {
                ST[i + 1][j] = min(ST[i][j], ST[i][j + (1 << i)]);
            }
        }
    }

public:
    sparseTable(const int size, const int first){
        build(first, size);
    }

    const int get(int l, int r){
        if (l > r) swap(l, r); l--;
        int d = 31 - __builtin_clz(r - l);
        return min(ST[d][l], ST[d][r - (1 << d)]);
    }
    const int size(){
        return ST[0].size();
    }
};

void solve() {
    ll n, m, a1;
    cin >> n >> m >> a1;
    sparseTable table(n, a1);
    ll v1, u1, ans;
    cin >> u1 >> v1;
    for (int i = 1; i < m; i++){
        ans = table.get(u1, v1);
        u1 = (17 * u1 + 751 + ans + 2 * i) % n + 1;
        v1 = (13 * v1 + 593 + ans + 5 * i) % n + 1;
    }
    ans = table.get(v1, u1);
    cout << u1 << " " << v1 << " " << ans;
}


int32_t main() {
    setlocale(LC_ALL, "Russian");
#ifdef __APPLE__
    std::freopen("input.txt", "r", stdin);
    std::freopen("output.txt", "w", stdout);
#endif
    std::cin.tie(0);
    std::ios_base::sync_with_stdio(false);
//    int t;
//    cin >> t;
//    for (int i = 0; i < t; i++)
    solve();
    return 0;
}