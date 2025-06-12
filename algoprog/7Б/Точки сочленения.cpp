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
vector<int> tin, tout;
int times = 0;
vector<vector<pair<int, int> > > gr;
set<int> vertexes;
void dfs(int v, int p){
    used[v] = 1;
    tin[v] = tout[p] = ++times;
    int cnt = 0;
    for (auto [to, num] : gr[v]){
        if (to == p) continue;
        if (used[to])
            tout[v] = min(tout[v], tin[to]);
        else {
            dfs(to, v);
            cnt++;
            tout[v] = min(tout[v], tout[to]);
            if (p != v && tout[to] >= tin[v]){
                vertexes.insert(v + 1);
            }
        }
    }
    if (p == v && cnt >= 2)
        vertexes.insert(v + 1);
}

void solve() {
    int n, m;
    cin >> n >> m;
    gr.resize(n);
    tin.resize(n, 1e9); tout.resize(n, 1e9); used.resize(n, 0);
    for (int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        gr[a - 1].push_back({b - 1, i + 1});
        gr[b - 1].push_back({a - 1, i + 1});
    }
    for (int i = 0; i < n; i++) 
        if (!used[i]) dfs(i, i);
    
    cout << vertexes.size() << "\n";
    for (auto i : vertexes) cout << i << ' ';
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