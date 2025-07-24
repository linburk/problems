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
        ancestor[a] = b;
    }
    inline void reset(int n){
        rank.resize(n, 1);
        ancestor.resize(n);
        iota(ancestor.begin(), ancestor.end(), 0);
    }
    inline int leader(int v){
        return (ancestor[v] == v ? v : v = leader(ancestor[v]));
    }
private:
    vector<int> ancestor, rank;
};

void solve(){
    _dsu dsu;
    string query;
    while (cin >> query){
        if (query == "RESET"){
            int n;
            cin >> n;
            dsu.reset(n + 1);
            cout << "RESET DONE\n";
        }
        if (query == "JOIN"){
            int a, b;
            cin >> a >> b;
            if (dsu.leader(a) == dsu.leader(b)) cout << "ALREADY " << a << " " << b << "\n";
            dsu.unite(a, b);
        }
    
        if (query == "CHECK"){
            int a, b;
            cin >> a >> b;
            cout << (dsu.leader(a) == dsu.leader(b) ? "YES\n" : "NO\n");
        }
    }
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