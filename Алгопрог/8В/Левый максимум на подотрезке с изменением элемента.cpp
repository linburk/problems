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

class segment_tree{
    struct node {
        int value;
        int pos;
    };
    void update(int n){
        int ls = n << 1, rs = n << 1 | 1;
        if (tree[ls].value >= tree[rs].value){
            tree[n].pos = tree[ls].pos;
            tree[n].value = tree[ls].value;
        } else {
            tree[n].pos = tree[rs].pos;
            tree[n].value = tree[rs].value;
        }
    }
    void build(vi &a, int l, int r, int n){
        if (l == r - 1) return (void)(tree[n].value = a[l], tree[n].pos = l);
        int m = (l + r) >> 1, ls = n << 1, rs = n << 1 | 1;
        build(a, l, m, ls), build(a, m, r, rs);
        update(n);
    }
    void update(int i, int x, int l, int r, int n){
        if (l > i || r <= i) return;
        if (l == r - 1) return (void)(tree[n].value = x);
        int m = (l + r) >> 1, ls = n << 1, rs = n << 1 | 1;
        update(i, x, l, m, ls), update(i, x, m, r, rs);
        update(n);
    }
    node get(int ql, int qr, int l, int r, int n){
        if (l >= qr || r <= ql) return {INT_MIN, -1};
        if (ql <= l && r <= qr) return tree[n];
        int m = (l + r) >> 1, ls = n << 1, rs = n << 1 | 1;
        node lg = get(ql, qr, l, m, ls), rg = get(ql, qr, m, r, rs);
        return lg.value >= rg.value ? lg : rg;
    }
protected:
    vector<node> tree;
    int tsize;
public:
    segment_tree(vi &a){
        tsize = (int)a.size();
        tree.resize(4 * tsize);
        build(a, 0, tsize, 1);
    }
    void update(int i, int x){
        return update(i, x, 0, tsize, 1);
    }
    int get(int ql, int qr){
        return get(ql, qr, 0, tsize, 1).pos;
    }
};

void solve() {
    int n, m;
    cin >> n;
    vi a(n);
    cin >> a;
    cin >> m;
    segment_tree tr(a);
    for (int i = 0; i < m; i++){
        char c;
        cin >> c;
        if (c == 's'){
            int l, r;
            cin >> l >> r;
            cout << tr.get(l - 1, r) + 1 << " ";
        }
        if (c == 'u'){
            int pos, x;
            cin >> pos >> x;
            tr.update(pos - 1, x);
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