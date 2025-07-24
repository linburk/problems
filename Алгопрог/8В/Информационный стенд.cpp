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
    struct node {
        int free;
    };
    void build(int w, int l, int r, int n){
        if (l == r - 1) return static_cast<void>(tree[n].free = w);
        int m = (l + r) >> 1, ls = n << 1, rs = n << 1 | 1;
        build(w, l, m, ls), build(w, m, r, rs);
        tree[n].free = max(tree[ls].free, tree[rs].free);
    }
    void update(int i, int w, int l, int r, int n){
        if (l > i || r <= i) return;
        if (l == r - 1) return static_cast<void>(tree[n].free -= w);
        int m = (l + r) >> 1, ls = n << 1, rs = n << 1 | 1;
        update(i, w, l, m, ls), update(i, w, m, r, rs);
        tree[n].free = max(tree[ls].free, tree[rs].free);
    }
    int get_max(int ql, int qr, int l, int r, int n){
        if (l >= qr || r <= ql) return 0;
        if (ql <= l && r <= qr) return tree[n].free;
        int m = (l + r) >> 1, ls = n << 1, rs = n << 1 | 1;
        return max(get_max(ql, qr, l, m, ls), get_max(ql, qr, m, r, rs));
    }
    int dfs(int w, int l, int r, int n){
        if (l == r - 1) return l;
        int m = (l + r) >> 1;
        int lg = get_max(l, m), rg = get_max(m, r);
        if (lg >= w) return dfs(w, l, m, n >> 1);
        else if (rg >= w) return dfs(w, m, r, n >> 1 | 1);
        return -1;
    }
protected:
    vector<node> tree;
    int tsize;
public:
    segtree(int n, int w){
        tsize = n;
        tree.resize(4 * n);
        build(w, 0, tsize, 1);
    }
    void update(int i, int w){
        return update(i, w, 0, tsize, 1);
    }
    int get_max(int ql, int qr){
        return get_max(ql, qr, 0, tsize, 1);
    }
    int get(int w){
        return dfs(w, 0, tsize, 1);
    }
};

void solve() {
    int h, w, n;
    cin >> h >> w >> n;
    h = min(h, n);
    segtree tr(h, w);
    for (int i = 0; i < n; i++){
        int wi;
        cin >> wi;
        int pos = tr.get(wi);
        cout << (pos == -1 ? -1 : pos + 1) << "\n";
        tr.update(pos, wi);
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