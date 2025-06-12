#include <bits/stdc++.h>
using namespace std;
 
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<vi> vvi;
typedef vector<vl> vvl;
typedef vector<bool> vb;
typedef vector<vector<bool> > vvb;
 
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
//        os << "\n";
        return os;
    }
    template <typename T, typename V>
    std::istream &operator>>(std::istream &is, std::pair<T, V> &p) {
        is >> p.first >> p.second;
        return is;
    }
}  // namespace tools
 
using namespace tools;

vi ans;
void dfs(int v, vvi &gr){
    for (int i = 0; i < gr.size(); i++){
        if (gr[v][i]){
            gr[v][i]--;
            gr[i][v]--;
            dfs(i, gr);
        }
    }
    ans.push_back(v + 1);
}

void solve() {
    int n;
    cin >> n;
    vvi gr(n, vi(n, 0));
    for (int i = 0; i < n; i++){
        int m;
        cin >> m;
        for (int j = 0; j < m; j++){
            int to, d;
            cin >> to >> d;
            gr[i][to - 1]++;
//            gr[to - 1][i]++;
        }
    }
    dfs(0, gr);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (gr[i][j]) return void(cout << -1);
        }
    }
    cout << ans.size() << "\n" << ans;
    
}
int32_t main() {
    setlocale(LC_ALL, "Russian");
#ifdef __APPLE__
    std::freopen("/Users/dmitrii/Documents/Code/Code/input.txt", "r", stdin);
    std::freopen("/Users/dmitrii/Documents/Code/Code/output.txt", "w", stdout);
#endif
    std::cin.tie(0);
    std::ios_base::sync_with_stdio(false);
//    int t; cin >> t; for (; t; t--)
    solve();
    return 0;
}