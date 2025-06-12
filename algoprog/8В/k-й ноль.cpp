#include <bits/stdc++.h>

using namespace std;

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


template<typename T = long long>
class segment_tree{

    struct node{
        T value;
        node() {}
        explicit node(T value): value(value) {}
    };

    static const int MAX_SIZE = 2 * 1E5 + 100;
    static const int INF = 1E9 + 100;
    node tree[MAX_SIZE * 4];

public:
    segment_tree(){
        memset(tree, 0, sizeof tree);
    }

    void build(const std::vector<T> &arr, const int n = 1, const int l = 0, const int r = MAX_SIZE){
        if (l == r){
            tree[n].value = (arr[l] == 0 ? 1 : 0);
            return;
        }
        int mid = (l + r) >> 1, ls = n << 1, rs = n << 1 | 1;
        build(arr, ls, l, mid);
        build(arr, rs, mid + 1, r);
        tree[n].value = tree[ls].value + tree[rs].value;
    }

    void update(const int i, const T val, const int n = 1, const int l = 0, const int r = MAX_SIZE){
        if (r < i || l > i) return;
        if (l == r == i){
            tree[n].value = (val == 0 ? 1 : 0);
            return;
        }
        int m = (l + r) >> 1, ls = n << 1, rs = n << 1 | 1;
        update(i, val, ls, l, m);
        update(i, val, rs, m + 1, r);
        tree[n].value = tree[ls].value + tree[rs].value;
    }

    T get(const int k, const int ql = 0, const int qr = MAX_SIZE, const int n = 1, const int l = 0, const int r = MAX_SIZE) {
        if (k > tree[n].value) return -1;
        if (l == r) return l;
        int m = (l + r) >> 1, ls = n << 1, rs = n << 1 | 1;
        if (tree[ls].value >= k){
            return get(k, ql, qr, ls, l, m);
        } else {
            return get(k - tree[ls].value, ql, qr, rs, m + 1, r);
        }
    }

};

void solve() {
    segment_tree<int> tree;
    int n, k;
    cin >> n;
    vector<int> arr(2 * 1E5 + 100, 1E9);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    tree.build(arr, 1, 0, n);
    cin >> k;
    for (int i = 0; i < k; i++) {
        int kk;
        cin >> kk;
        int res = tree.get(kk, 0, n, 1, 0, n);
        cout << (res == -1 ? res : res + 1) << " ";
    }
}

int32_t main() {
    setlocale(LC_ALL, "Russian");
#ifdef __APPLE__
    std::freopen("input.txt", "r", stdin);
    std::freopen("output.txt", "w", stdout);
#endif
    std::cin.tie(0);
    std::cout.tie(0);
    std::ios_base::sync_with_stdio(false);
//    int t;
//    cin >> t;
//    for (int i = 0; i < t; i++)
    solve();
    return 0;
}