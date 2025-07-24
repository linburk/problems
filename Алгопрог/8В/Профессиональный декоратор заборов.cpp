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

class segtree{
    struct node{
        ull hash;
        ull bonus = 0;
    };
    void update(node &n, node &ls, node &rs, int l, int r){
        int m = (r + l) >> 1;
        n.hash = (ls.hash + rs.hash * powers[m - l] % mod) % mod;
    }
    void push(node &n, node &ls, node &rs, int l, int r){
        if (n.bonus == 0) return;
        int m = (r + l) >> 1;
        ls.hash = n.bonus * geomseries[m - l] % mod;
        rs.hash = n.bonus * geomseries[r - m] % mod;
        ls.bonus = n.bonus;
        rs.bonus = n.bonus;
        n.bonus = 0;
    }
    
    void build(vi &a, int l, int r, int n){
        if (l == r - 1) return (void)(tree[n].hash = a[l]);
        int m = (l + r) >> 1, ls = n << 1, rs = n << 1 | 1;
        build(a, l, m, ls), build(a, m, r, rs);
        update(tree[n], tree[ls], tree[rs], l, r);
    }
    void update(int ql, int qr, int k, int l, int r, int n){
        if (l >= qr || r <= ql) return;
        if (ql <= l && r <= qr){
            tree[n].hash = k * geomseries[r - l] % mod;
            tree[n].bonus = k;
            return;
        }
        int m = (l + r) >> 1, ls = n << 1, rs = n << 1 | 1;
        push(tree[n], tree[ls], tree[rs], l, r);
        update(ql, qr, k, l, m, ls), update(ql, qr, k, m, r, rs);
        update(tree[n], tree[ls], tree[rs], l, r);
    }
    ull get_hash(int ql, int qr, int l, int r, int n){
        if (l >= qr || r <= ql) return 0;
        if (ql <= l && r <= qr) return tree[n].hash;
        int m = (l + r) >> 1, ls = n << 1, rs = n << 1 | 1;
        push(tree[n], tree[ls], tree[rs], l, r);
        ull lg = get_hash(ql, qr, l, m, ls);
        ull rg = get_hash(ql, qr, m, r, rs);
        return (lg + rg * powers[max(0, m - ql)] % mod) % mod;
    }
protected:
    const ull p = 37, mod = 1E9 + 7;
    vector<ull> geomseries;
    vector<ull> powers;
    vector<node> tree;
    int tsize;
public:
    segtree(vi &a){
        tsize = (int)a.size();
        tree.resize(4 * tsize);
        powers.resize(tsize, 1);
        geomseries.resize(tsize + 1);
        for (int i = 0; i < tsize - 1; i++){
            powers[i + 1] = (powers[i] * p) % mod;
        }
        for (int i = 0; i < tsize; i++){
            geomseries[i + 1] = (geomseries[i] + powers[i]) % mod;
        }
        build(a, 0, tsize, 1);
    }
    void update(int ql, int qr, int k){
        return update(ql, qr, k, 0, tsize, 1);
    }
    ull get_hash(int ql, int qr){
        return get_hash(ql, qr, 0, tsize, 1);
    }
};

void solve() {
    int n, m;
    cin >> n;
    vi a(n);
    cin >> a >> m;
    segtree tree(a);
//    cout << tree.get_hash(4, 6);
    for (int i = 0; i < m; i++){
        int q, l, r, k;
        cin >> q >> l >> r >> k;
        if (q == 0){
            tree.update(l - 1, r, k);
        }
        if (q == 1){
            ull lq = tree.get_hash(l - 1, l - 1 + k);
            ull rq = tree.get_hash(r - 1, r - 1 + k);
            cout << (lq == rq ? "+" : "-");
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