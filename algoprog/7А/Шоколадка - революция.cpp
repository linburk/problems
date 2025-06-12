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
        return os;
    }
    template <typename T, typename V>
    std::istream &operator>>(std::istream &is, std::pair<T, V> &p) {
        is >> p.first >> p.second;
        return is;
    }
}  // namespace tools
 
using namespace tools;
vector<int> max_cost;
vector<vector<int> > gr;

int dfs(int v, int pl){
    bool fl = 0;
    for (auto to : gr[v]){
        if (pl == 0) {
            max_cost[v] = max(max_cost[v], dfs(to, pl ^ 1));
        }
        else {
            if (!fl) {
                max_cost[v] = dfs(to, pl ^ 1);
                fl = 1;
            } else {
                max_cost[v] = min(max_cost[v], dfs(to, pl ^ 1));
            }
        }
    }
    return max_cost[v];
}

void solve() {
    int n;
    cin >> n;
    gr.resize(n);
    max_cost.resize(n);
    for (int i = 0; i < n; i++){
        int anc, c;
        cin >> anc >> c;
        if (anc != 0) {
            gr[anc - 1].push_back(i);
        }
        max_cost[i] = c;
    }
    cout << dfs(0, 0);
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