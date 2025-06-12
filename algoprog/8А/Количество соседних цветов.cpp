#include <bits/stdc++.h>
#include <climits>

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
typedef vector<vb> vvb;
typedef vector<vvi> vvvi;
typedef vector<vvl> vvvl;
typedef vector<char> vc;
typedef vector<vc> vvc;
typedef pair<int, int> pi;
typedef pair<ll, ll> pl;
typedef vector<pi> vpi;
typedef vector<pl> vpl;
typedef vector<vpi> vvpi;
typedef vector<vpl> vvpl;

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
} // namespace tools

using namespace tools;

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    vi color(n);
    cin >> color;
    vvi gr(n);
    for (int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        gr[a - 1].push_back(b - 1);
        gr[b - 1].push_back(a - 1);
    }
    const int BLOCK_SIZE = 555;
    vvi heavy_gr(n);
    vb is_heavy(n);
    vector<map<int, int> > color_cnt(n);
    for (int i = 0; i < n; i++){
        if (gr[i].size() > BLOCK_SIZE){
            is_heavy[i] = 1;
            for (auto to : gr[i]){
                heavy_gr[to].push_back(i);
                color_cnt[i][color[to]]++;
            }
        }
    }
    for (int i = 0; i < q; i++){
        int comm;
        cin >> comm;
        if (comm == 1){
            int v, c;
            cin >> v >> c;
            v--;
            for (auto to : heavy_gr[v]){
                color_cnt[to][color[v]]--;
                if (color_cnt[to][color[v]] == 0) color_cnt[to].erase(color[v]);
                color_cnt[to][c]++;
            }
            color[v] = c;
        }
        if (comm == 2){
            int v;
            cin >> v;
            v--;
            int res = 0;
            if (is_heavy[v]){
                res = color_cnt[v].size();
            } else {
                map<int, int> have;
                for (auto to : gr[v]){
                    if (!have[color[to]]){
                        have[color[to]] = 1;
                        res++;
                    }
                }
            }
            cout << res << "\n";
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
//    for (int i=0;i<t;i++)
    solve();
    return 0;
}