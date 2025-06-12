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
typedef map<int, int> mi;
typedef map<ll, ll> ml;
typedef vector<mi> vmi;
typedef vector<ml> vml;
typedef set<int> si;
typedef set<ll> sl;
typedef vector<si> vsi;
typedef vector<sl> vsl;
typedef unordered_map<int, int> umi;
typedef unordered_map<ll, ll> uml;

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

const int MAXSIZE = 1E5 + 1;

class lca{
    vvi binup;
    vi depth;
    void dfs(vvi &gr, int v, int p){
        depth[v] = depth[p] + 1;
        binup[v][0] = p;
        for (int i = 1; i < 32; i++){
            binup[v][i] = binup[binup[v][i - 1]][i - 1];
        }
        for (auto to : gr[v]) if (to != p) dfs(gr, to, v);
    }
public:
    int get_lca(int a, int b){
        if (depth[a] < depth[b]) swap(a, b);
        for (int i = 31; i >= 0; i--){
            if (depth[binup[a][i]] >= depth[b]) a = binup[a][i];
        }
        if (a == b) return a;
        for (int i = 31; i >= 0; i--){
            if (binup[a][i] != binup[b][i]) a = binup[a][i], b = binup[b][i];
        }
        return binup[a][0];
    }
    int get_dist(int a, int b){
        int ab = get_lca(a, b);
        return depth[a] + depth[b] - 2 * depth[ab];
        
    }
    void build(vvi &gr){
        depth.resize(gr.size());
        binup.resize(gr.size(), vi(32));
        depth[0] = -1;
        dfs(gr, 0, 0);
    }
    lca(vvi &gr){
        build(gr);
    }
    lca(){}
};

lca _lca;
vvi gr;
vi optimal;
const int BLOCKSIZE = 555;
vi red;
int ans_query(int v){
    int res = optimal[v];
    for (auto i : red) res = min(res, _lca.get_dist(v, i));
    return res;
}

void rebuild(){
    for (int v = 0; v < gr.size(); v++){
        optimal[v] = ans_query(v);
    }
    red.clear();
}
void solve() {
    int n, m;
    cin >> n >> m;
    gr.resize(n);
    optimal.resize(n, 1e9);
    for (int i = 0; i < n - 1; i++){
        int a, b;
        cin >> a >> b;
        gr[a - 1].push_back(b - 1);
        gr[b - 1].push_back(a - 1);
    }
    _lca.build(gr);
    red.push_back(0);
    for (int i = 0; i < m; i++){
        int comm, v;
        cin >> comm >> v; v--;
        if (comm == 1){
            red.push_back(v);
        }
        if (comm == 2){
            cout << ans_query(v) << "\n";
        }
        if (red.size() == BLOCKSIZE){
            rebuild();
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