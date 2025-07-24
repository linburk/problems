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

vector<bool> is_cut;
vector<int> depth;
vector<vector<int> > gr;
int dfs(int v, int p){
    depth[v] = depth[p] + 1;
    int minD = 1e9;
    int cnt = 0;
    for (auto to : gr[v]){
        if (to == p) continue;
        if (depth[to])
            minD = min(minD, depth[to]);
        else if (!depth[to]){
            int temp = dfs(to, v);
            minD = min(minD, temp);
            (temp >= depth[v] && p != v ? void(is_cut[v] = 1) : void());
            cnt++;
        }
    }
    (cnt >= 2 && p == v ? void(is_cut[v] = 1) : void());
    return minD;
}
bool used[20001];
vi ans;
bool finded = 0;
void findPath(int s, int e){
    if (s == e){
        finded = 1;
        return;
    }
    if (used[s]) return;
    used[s] = 1;
    for (auto to : gr[s]){
        if (!finded)
            findPath(to, e);
    }
    if (finded){
        if (is_cut[s]){
            ans.push_back(s + 1);
        }
        return;
    }
}
void solve() {
    int n, m;
    cin >> n >> m;
    gr.resize(n); depth.resize(n, 0); is_cut.resize(n, 0);
    while (m--){
        int a, b;
        cin >> a >> b;
        gr[a - 1].push_back(b - 1);
        gr[b - 1].push_back(a - 1);
    }
    int s, e;
    cin >> s >> e;
    dfs(s - 1, s - 1);
    findPath(s - 1, e - 1);
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