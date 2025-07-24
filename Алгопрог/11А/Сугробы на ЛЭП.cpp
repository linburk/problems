#include <bits/stdc++.h>
//#include <ext/pb_ds/detail/standard_policies.hpp>

using namespace std;
//using namespace __gnu_pbds;

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

#define endl '\n'
#define all(cont) cont.begin(), cont.end()
#define unique(cont) cont.erase(unique(all(cont)), cont.end())
#define pb(x) emplace_back(x)

namespace tools {

    template <typename T>
    T gcd(T a, T b) {
        while (b > 0) {
            a %= b;
            std::swap(a, b);
        }
        return a;
    }

    template <typename T>
    T lcm(T a, T b) {
        return a * b / gcd(a, b);
    }

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

class segmentTree{

    struct node{
        int left;
        int right;
        int value;
        int bonus = 0;
    };

    vector<node> tree;

    inline void update(node &cur){
        cur.value = tree[cur.left].value + tree[cur.right].value;
    }

    void build(const std::vector<int> &arr, const int n, const int l, const int r){
        if (l == r){
            tree[n].value = arr[l];
            return;
        }
        int mid = (l + r) >> 1;
        tree[n].left = n << 1;
        tree[n].right = n << 1 | 1;
        build(arr, tree[n].left, l, mid);
        build(arr, tree[n].right, mid + 1, r);
        update(tree[n]);
    }

    void update(const int ql, const int qr, const int val, const int n, const int l, const int r){
        if (l > qr || r < ql) return;
        tree[n].value += (min(qr, r) - max(l, ql) + 1) * val;
        if (l >= ql && r <= qr){
            tree[n].bonus += val;
            return;
        }
        int m = (l + r) >> 1;
        update(ql, qr, val, tree[n].left, l, m);
        update(ql, qr, val, tree[n].right, m + 1, r);
        update(tree[n]);
    }

    int get(const int ql, const int qr, const int n, const int l, const int r){
        if (l > qr || r < ql) return 0;
        if (l >= ql && r <= qr) return tree[n].value;
        int m = (l + r) >> 1;
        int _l = get(ql, qr, tree[n].left, l, m);
        int _r = get(ql, qr, tree[n].right, m + 1, r);
        return _l + _r + (min(qr, r) - max(l, ql) + 1) * tree[n].bonus;
    }

    int tsize;

public:

    segmentTree(const std::vector<int> &arr){
        tree.resize(4 * arr.size());
        tsize = arr.size();
        build(arr, 1, 0, arr.size() - 1);
    }

    segmentTree(size_t size, int elem){
        tree.resize(4 * size);
        tsize = size;
        vector<int> *temp = new vector<int>(size, elem);
        build(*temp, 1, 0, size - 1);
        delete temp;
    }

    void update(int ql, int qr, int val){
        update(ql, qr, val, 1, 0, tsize - 1);
    }

    int get(int ql, int qr){
        return get(ql, qr, 1, 0, tsize - 1);
    }

    int size(){
        return tsize;
    }
};


void solve() {
    int n, k;
    cin >> n >> k;
    segmentTree tree(vector<int>(n, 0));
    for (int i = 0; i < k; i++){
        int com;
        cin >> com;
        if (com == 1){
            int l, r, s;
            cin >> l >> r >> s;
            tree.update(l, r - 1, s);
        } else {
            int l, r;
            cin >> l >> r;
//            for (int j = l; j < r; j++) cout << tree.get(j, j) << " ";
            cout << tree.get(l, r - 1) << endl;
        }
    }
}


int32_t main() {
    setlocale(LC_ALL, "Russian");
#ifdef __APPLE__
    std::freopen("input.txt", "r", stdin);
    std::freopen("output.txt", "w", stdout);
#endif
    std::cin.tie(0);
    std::ios_base::sync_with_stdio(false);
//    int t;
//    cin >> t;
//    for (int i = 0; i < t; i++)
    solve();
    return 0;
}