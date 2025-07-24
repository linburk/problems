#include <bits/stdc++.h>
using namespace std;
 
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
 
#define all(cont) cont.begin(), cont.end()
#define funique(cont) cont.erase(unique(all(cont)), cont.end())

namespace tools {
mt19937_64 rng(chrono::steady_clock().now().time_since_epoch().count());
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
        os << "\n";
        return os;
    }
    template <typename T, typename V>
    std::istream &operator>>(std::istream &is, std::pair<T, V> &p) {
        is >> p.first >> p.second;
        return is;
    }
}  // namespace tools
 
using namespace tools;

vector<bool> used;
vector<int> depths, mins;
vector<vector<pair<int, int> > > gr;
vector<int> bridges;
void dfs(int v, int p){
    used[v] = 1;
    depths[v] = mins[v] = (depths[p] + 1);
    for (auto [to, num] : gr[v]){
        if (to == p) continue;
        if (used[to])
            mins[v] = min(mins[v], depths[to]);
        else {
            dfs(to, v);
            mins[v] = min(mins[v], mins[to]);
            if (depths[v] < mins[to]) bridges.push_back(num);
        }
    }
    
}

void solve() {
    int n, m;
    cin >> n >> m;
    gr.resize(n);
    depths.resize(n, 0); mins.resize(n, 1e9); used.resize(n, 0);
    for (int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        gr[a - 1].push_back({b - 1, i + 1});
        gr[b - 1].push_back({a - 1, i + 1});
    }
    dfs(0, 0);
    cout << bridges.size() << "\n" << bridges;
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