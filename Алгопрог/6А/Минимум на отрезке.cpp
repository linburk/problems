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

class binary_heap{

    std::vector<int> tree;

    void sift_up(int node){
        while (node > 1 and tree[node] < tree[node / 2]){
            swap(tree[node], tree[node / 2]);
            node /= 2;
        }
    }

    void sift_down(int node){
        while (node * 2 < tree.size()){
            int next = ((node * 2 + 1) < tree.size() and tree[node * 2 + 1] < tree[node * 2] ? node * 2 + 1 : node * 2);
            if (tree[node] <= tree[next])
                break;
            swap(tree[node], tree[next]);
            node = next;
        }
    }

    size_t heap_size = 0;

public:

    binary_heap(){
        tree.reserve(1E6 + 1);
        tree.resize(1);
    }

    void insert(int x){
        tree.push_back(x);
        sift_up(tree.size() - 1);
        heap_size++;
    }

    void pop(){
        swap(tree[1], tree[tree.size() - 1]);
        tree.erase(tree.end() - 1);
        if (tree.size()) sift_down(1);
        heap_size--;
    }

    int top(){
        return tree[1];
    }

    int size(){
        return heap_size;
    }

};

void solve(){
    binary_heap heap;
    binary_heap deleted;
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    cin >> a;
    for (int i = 0; i < k; i++)
        heap.insert(a[i]);
    cout << heap.top() << endl;
    for (int i = k; i < n; i++){
        deleted.insert(a[i - k]);
        heap.insert(a[i]);
        while (deleted.size() && deleted.top() == heap.top()){
            deleted.pop();
            heap.pop();
        }
        cout << heap.top() << endl;
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