#include <bits/stdc++.h>
using namespace std;
 
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
 
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

template<typename T>
class cartesianTree{
    static mt19937_64 rng64_t;
    
    struct Node{
        T key;
        unsigned priority, size;
        Node *left, *right;
        Node(T key): key(key), priority(rng64_t()), left(0), right(0), size(1) {}
        Node(){}
    } *root = nullptr;
    
    static void update(Node *node){
        node ? node->size = size(node->left) + 1 + size(node->right) : 0;
    }
    static size_t size(Node *node){
        return node ? node->size : 0;
    }
    
    static void split(Node *node, T key, Node *&left, Node *&right){
        if (!node) {left = right = 0; return; }
        if (node->key > key){
            split(node->right, key, node->right, right);
            left = node;
            update(left);
        } else {
            split(node->left, key, left, node->left);
            right = node;
            update(right);
        }
    }
    
    static Node* merge(Node *left, Node *right){
        if (!left || !right) return right ? right : left;
        if (left->priority > right->priority){
            left->right = merge(left->right, right);
            update(left);
            return left;
        } else {
            right->left = merge(left, right->left);
            update(right);
            return right;
        }
    }
    static T get_key(size_t index, Node* node ){
        size_t leftSize = size(node->left);
        if (index == leftSize) return node->key;
        if (index < leftSize) return get_key(index, node->left);
        return get_key(index - leftSize - 1, node->right);
    }
    static size_t get_index(T key, Node* node){
        Node *left, *right;
        split(node, key, left, right);
        size_t result = size(left);
        node = merge(left, right);
        return result;
    }
public:
    T get_key(size_t index){
        return get_key(index, root);
    }
    size_t get_index(T key){
        return get_index(key, root);
    }
    void insert(T key){
        Node *left, *right;
        split(root, key, left, right);
        root = merge(merge(left, new Node(key)), right);
    }
    void erase(T key){
        Node *left, *right, *equal;
        split(root, key, left, right);
        split(right, key + 1, equal, right);
        root = merge(left, right);
    }
    
};
template<> mt19937_64 cartesianTree<ll>::rng64_t(chrono::steady_clock().now().time_since_epoch().count());

void solve() {
    cartesianTree<ll> tree;
    int n;
    cin >> n;
    while (n--){
        int c, x;
        cin >> c >> x;
        if (c & 1){
            tree.insert(x);
            cout << tree.get_index(x) << '\n';
        } else {
            tree.erase(tree.get_key(x));
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