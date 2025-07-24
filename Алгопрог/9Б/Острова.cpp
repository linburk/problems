#include <bits/stdc++.h>
using namespace std;

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

#define endl '\n'
#define all(cont) cont.begin(), cont.end()
#define unique(cont) cont.erase(unique(all(cont)), cont.end())

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

class _dsu{
public:
    inline void unite(int a, int b){
        a = leader(a), b = leader(b);
        if (rank[a] > rank[b]) swap(a, b);
        rank[b] = max(rank[b], rank[a] + 1);
        if (a != b) weight[b] += weight[a];
        ancestor[a] = b;
    }
    _dsu(int n){
        weight.resize(n, 1);
        rank.resize(n, 1);
        ancestor.resize(n);
        iota(ancestor.begin(), ancestor.end(), 0);
    }
    inline int leader(int v){
        return (ancestor[v] == v ? v : v = leader(ancestor[v]));
    }
    inline int w(int v){
        v = leader(v);
        return weight[v];
    }
private:
    vector<int> ancestor, rank, weight;
};

void solve(){
    int n, m;
    cin >> n >> m;
    int ans = 1e9;
    _dsu dsu(n);
    for (int i = 1; i <= m; i++){
        int x, y;
        cin >> x >> y;
        dsu.unite(x, y);
        if (dsu.w(x) == n){ 
            ans = min(ans, i);
        }
    }
    cout << ans;
}

int32_t main() {
    setlocale(LC_ALL, "Russian");
#ifdef __APPLE__
    std::freopen("/Users/dmitrii/Documents/Code/Code/input.txt", "r", stdin);
    std::freopen("/Users/dmitrii/Documents/Code/Code/output.txt", "w", stdout);
#endif
    std::cin.tie(0);
    std::ios_base::sync_with_stdio(false);
//    int t;
//    cin >> t;
//    for (int i = 0; i < t; i++)
    solve();
    return 0;
}