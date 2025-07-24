#include <bits/stdc++.h>
using namespace std;
 
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
 
#define all(cont) cont.begin(), cont.end()
#define funique(cont) cont.erase(unique(all(cont)), cont.end())
 
namespace tools {
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
    template <typename T>
    std::istream &operator>>(std::istream &is,
                             std::vector<std::vector<T> > &matrix) {
        for (auto &i : matrix)
            for (auto &j : i) is >> j;
        return is;
    }
    template <typename T>
    std::ostream &operator<<(std::ostream &os,
                             const std::vector<std::vector<T> > &matrix) {
        for (const auto &i : matrix) {
            for (const auto &j : i) os << j << " ";
            os << "\n";
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

// MIN MASS ST
class segmentTree{
public:
    segmentTree(int n, int val){
        tree.resize(4 * n);
        vector<ll> temp(n, val);
        tsize = n;
        build(temp, 0, tsize - 1, 1);
    }
    
    ll get(int ql, int qr){
        return get(ql, qr, 0, tsize - 1, 1);
    }

    segmentTree(vector<ll> &array){
        tree.resize(4 * array.size());
        tsize = array.size();
        build(array, 0, tsize - 1, 1);
    }

    void update(int ql, int qr, int val){
        update(val, ql, qr, 0, tsize - 1, 1);
    }
private:
    
    struct node{
        ll value;
        ll bonus = 0;
    };
    
    vector<node> tree;
    size_t tsize;

    void push(int v, int ls, int rs){
        if (tree[v].bonus != 0){
            tree[ls].value += tree[v].bonus;
            tree[rs].value += tree[v].bonus;
            tree[ls].bonus += tree[v].bonus;
            tree[rs].bonus += tree[v].bonus;
            tree[v].bonus = 0;
        }
    }
    
    void build(vector<ll> &array, int l, int r, int v){
        if (l == r){
            tree[v].value = array[l];
            return;
        }
        int m = (l + r) >> 1, ls = v << 1, rs = v << 1 | 1;
        build(array, l, m, ls);
        build(array, m + 1, r, rs);
        tree[v].value = max(tree[ls].value, tree[rs].value);
    }
    
    void update(int val, int ql, int qr, int l, int r, int v){
        if (l > qr || r < ql) return;
        if (l >= ql && r <= qr){
            tree[v].value += val;
            tree[v].bonus += val;
            return;
        }
        int m = (l + r) >> 1, ls = v << 1, rs = v << 1 | 1;
        push(v, ls, rs);
        update(val, ql, qr, l, m, ls);
        update(val, ql, qr, m + 1, r, rs);
        tree[v].value = max(tree[ls].value, tree[rs].value);
    }
    
    ll get(int ql, int qr, int l, int r, int v){
        if (l > qr || r < ql) return INT_MIN;
        if (l >= ql && r <= qr){
            return tree[v].value;
        }
        int m = (l + r) >> 1, ls = v << 1, rs = v << 1 | 1;
        push(v, ls, rs);
        ll _lg = get(ql, qr, l, m, ls);
        ll _rg = get(ql, qr, m + 1, r, rs);
        return max(_lg, _rg);
    }
    
};


void solve() {
    int n, m;
    cin >> n;
    vector<ll> a(n);
    cin >> a;
    segmentTree tree(a);
    cin >> m;
    for (int i = 0; i < m; i++){
        char c;
        cin >> c;
        if (c == 'm'){
            int l, r;
            cin >> l >> r;
            cout << tree.get(l - 1, r - 1) << " ";
        } else {
            int l, r, val;
            cin >> l >> r >> val;
            tree.update(l - 1, r - 1, val);
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
//    for (int i = 0; i < t; i++)
    solve();
    return 0;
}