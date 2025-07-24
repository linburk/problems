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
        int value = 0;
        int bonus = -1;
        pair<int, int> bonusborder = {-1, -1};
        pair<int, int> borders;
    };

    vector<node> tree;

    inline void update(node &cur){
        cur.value = tree[cur.left].value + tree[cur.right].value;
    }
    inline void push(node &cur){
        if (cur.bonus != -1) {
            tree[cur.left].value = cur.bonus;
            tree[cur.right].value = cur.bonus;
            tree[cur.left].bonus = cur.bonus;
            tree[cur.right].bonus = cur.bonus;
            cur.bonus = -1;
        }
        if (cur.bonusborder != make_pair(-1, -1)) {
            tree[cur.left].borders = cur.bonusborder;
            tree[cur.right].borders = cur.bonusborder;
            tree[cur.left].bonusborder = cur.bonusborder;
            tree[cur.right].bonusborder = cur.bonusborder;
            cur.bonusborder = {-1, -1};
        }
    }

    void build(const std::vector<int> &arr, const int n, const int l, const int r){
        if (l == r) return;
        int mid = (l + r) >> 1;
        tree[n].left = n << 1;
        tree[n].right = n << 1 | 1;
        build(arr, tree[n].left, l, mid);
        build(arr, tree[n].right, mid + 1, r);
        update(tree[n]);
    }

    int get(const int i, const int n, const int l, const int r){
        if (r < i || l > i) return 0;
        if (r == l && l == i) {
            return tree[n].value;
        }
        push(tree[n]);
        int m = (l + r) >> 1;
        int _l = get(i, tree[n].left, l, m);
        int _r = get(i, tree[n].right, m + 1, r);
        return max(_l, _r);
    }

    pair<int, int> get_lr(const int i, const int n, const int l, const int r){
        if (r < i || l > i) return {1e9, -1e9};
        if (r == l && l == i) {
            return tree[n].borders;
        }
        push(tree[n]);
        int m = (l + r) >> 1;
        pair<int, int> _l = get_lr(i, tree[n].left, l, m);
        pair<int, int> _r = get_lr(i, tree[n].right, m + 1, r);
        return {min(_l.first, _r.first), max(_l.second, _r.second)};
    }

    bool check_lr(const int ql, const int qr, const int n, const int l, const int r){
        if (l > qr || r < ql) return 1;
        if (l >= ql && r <= qr) return tree[n].value == 0;
        push(tree[n]);
        int m = (l + r) >> 1;
        bool _l = check_lr(ql, qr, tree[n].left, l, m);
        bool _r = check_lr(ql, qr, tree[n].right, m + 1, r);
        return _l & _r;
    }

    void update(const int ql, const int qr, int val, const int n, const int l, const int r){
        if (l > qr || r < ql) return;
        if (l >= ql && r <= qr) {
            tree[n].value = val;
            tree[n].bonus = val;
            tree[n].borders = {ql, qr};
            tree[n].bonusborder = {ql, qr};
            return;
        }
        push(tree[n]);
        int m = (l + r) >> 1;
        update(ql, qr, val, tree[n].left, l, m);
        update(ql, qr, val, tree[n].right, m + 1, r);
        update(tree[n]);
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

    int get(int i){
        return get(i, 1, 0, tsize - 1);
    }

    pair<int, int> get_lr(int i){
        return get_lr(i, 1, 0, tsize - 1);
    }

    bool check_lr(int ql, int qr){
        return check_lr(ql, qr, 1, 0, tsize - 1);
    }

    int size(){
        return tsize;
    }

};

void solve() {
    int n, k;
    cin >> n >> k;
    segmentTree tree(vector<int>(n, 0));
    for (int i = 1; i <= k; i++){
        int com;
        cin >> com;
        if (com == 1){
            int l, r;
            cin >> l >> r;
            l--; r--;
            if (tree.check_lr(l, r)){
                tree.update(l, r, i);
                cout << "1\n";
            } else cout << "0\n";

        } else {
            int ind;
            cin >> ind;
            int get = tree.get(ind - 1);
            if (get == 0){
                cout <<"0 0\n";
                continue;
            }
            pair<int, int> lr = tree.get_lr(ind - 1);
            tree.update(lr.first, lr.second, 0);
            cout << lr.first + 1 << " " << lr.second + 1 << "\n";
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