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

#define all(cont) cont.begin(), cont.end()
#define funique(cont) cont.erase(unique(all(cont)), cont.end())

namespace tools {
// mt19937_64 rng(chrono::steady_clock().now().time_since_epoch().count());
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
} // namespace tools

using namespace tools;

class segTree{
private:
    struct node{
        int val = 0;
        int lb, rb;
    };
    void update(int n){
        int ls = n << 1, rs = n << 1 | 1;
        tree[n].val = max(tree[n].val, tree[ls].val + tree[rs].val);
    }
    void build(const vector<pair<int, int> > &a, int n, int l, int r){
        if (r - l == 1) return (void)(tree[n].lb = a[l].first, tree[n].rb = a[l].second);
        int m = (l + r) >> 1, ls = n << 1, rs = n << 1 | 1;
        build(a, ls, l, m), build(a, rs, m, r);
        return (void)(tree[n].lb = tree[ls].lb, tree[n].rb = tree[rs].rb);
    }
    void update(int ql, int qr, int n, int l, int r){
        if (r <= ql || qr <= l) return;
        if (ql <= l && r <= qr) return (void)(tree[n].val = tree[n].rb - tree[n].lb);
        int m = (l + r) >> 1, ls = n << 1, rs = n << 1 | 1;
        update(ql, qr, ls, l, m), update(ql, qr, rs, m, r);
        update(n);
    }
    int get(int ql, int qr, int n, int l, int r){
        update(n);
        if (r <= ql || qr <= l) return 0;
        if (ql <= l && r <= qr) return tree[n].val;
        int m = (l + r) >> 1, ls = n << 1, rs = n << 1 | 1;
        return get(ql, qr, ls, l, m) + get(ql, qr, rs, m, r);
    }
protected:
    vector<node> tree;
    int tsize;
public:
    segTree(const vector<pair<int, int> > &a){ tree.resize(4 * a.size()), tsize = a.size(), build(a, 1, 0, tsize); }
    void update(int ql, int qr){ return update(ql, qr, 1, 0, tsize); }
    int get(int ql, int qr){ return get(ql, qr, 1, 0, tsize); }
};

void solve() {
    int n;
    cin >> n;
    vector<pair<int, int> > queries(n);
    for (int i = 0; i < n && cin >> queries[i].first >> queries[i].second; i++);
    set<int> points;
    for (auto [f, s] : queries) points.insert(f), points.insert(s);
    vi points_v(all(points));
    map<int, int> code;
    for (int i = 0; i < points_v.size(); i++) code[points_v[i]] = i;
    vector<pair<int, int> > segs;
    for (int i = 0; i < points_v.size() - 1; i++){
        segs.push_back({points_v[i], points_v[i + 1]});
    }
    if (segs.size() == 0) return (void) (cout << 0);

    segTree tree(segs);
    for (auto [f, s] : queries){
        if (f < s) tree.update(code[f], code[s]);
    }
    cout << tree.get(0, segs.size());
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
//    for (; t; t--)
    solve();
    return 0;
}