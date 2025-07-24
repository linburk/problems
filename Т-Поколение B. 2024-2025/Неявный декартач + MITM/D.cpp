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
std::istream& operator>>(std::istream& is, std::vector<T>& array)
{
    for (auto& i : array) {
        is >> i;
    }
    return is;
}
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& array)
{
    for (const auto& i : array) {
        os << i << " ";
    }
    return os;
}
template <typename T>
std::istream& operator>>(std::istream& is,
    std::vector<std::vector<T>>& matrix)
{
    for (auto& i : matrix)
        for (auto& j : i)
            is >> j;
    return is;
}
template <typename T>
std::ostream& operator<<(std::ostream& os,
    const std::vector<std::vector<T>>& matrix)
{
    for (const auto& i : matrix) {
        for (const auto& j : i)
            os << j << " ";
        os << "\n";
    }
    return os;
}
template <typename T, typename V>
std::istream& operator>>(std::istream& is, std::pair<T, V>& p)
{
    is >> p.first >> p.second;
    return is;
}
} // namespace tools

using namespace tools;

template <typename T>
class cartesianTree {
    static mt19937_64 rng64_t;

    struct Node {
        T value;
        T minVal;
        bool reversed = 0;
        unsigned priority, size;
        Node *left, *right;
        Node(T _value)
            : value(_value)
            , priority(rng64_t())
            , left(0)
            , right(0)
            , size(1)
            , minVal(value)
        {
        }
        Node() { }
    }* root = nullptr;

    void push(Node* node)
    {
        if (node && node->reversed) {
            swap(node->left, node->right);
            if (node->left)
                node->left->reversed ^= 1;
            if (node->right)
                node->right->reversed ^= 1;
            node->reversed = 0;
        }
    }
    void update(Node*& node)
    {
        if (node) {
            node->size = size(node->left) + 1 + size(node->right);
            node->minVal = min({ node->value, N_min(node->left), N_min(node->right) });
        }
    }

    T N_value(Node* node) { return node ? node->value : 0; }
    T N_min(Node* node) { return node ? node->minVal : NEUTRAL_MIN; }

    size_t size(Node* node) { return node ? node->size : 0; }
    void split(Node* node, T k, Node*& left, Node*& right)
    {
        push(node);
        if (!node) {
            left = right = nullptr;
            return;
        }
        if (size(node->left) < k) {
            split(node->right, k - size(node->left) - 1, node->right, right);
            left = node;
        } else {
            split(node->left, k, left, node->left);
            right = node;
        }
        update(left);
        update(right);
    }
    Node* merge(Node* left, Node* right)
    {
        push(left);
        push(right);
        if (!left || !right)
            return left ? left : right;
        if (left->priority > right->priority) {
            left->right = merge(left->right, right);
            update(left);
            return left;
        } else {
            right->left = merge(left, right->left);
            update(right);
            return right;
        }
    }

protected:
    static const long long NEUTRAL_MIN = LONG_LONG_MAX;

public:
    T operator[](size_t index) { return get(index); }
    cartesianTree() { }
    cartesianTree(vector<T>& arr)
    {
        for (auto& i : arr)
            push_back(i);
    }
    T size()
    {
        return size(root);
    }
    void push_back(T val) { root = merge(root, new Node(val)); }

    void insert(size_t index, T value)
    {
        Node *left, *right;
        split(root, index, left, right);
        root = merge(merge(left, new Node(value)), right);
    }
    void erase(size_t index)
    {
        Node *left, *right, *equal;
        split(root, index, left, right);
        split(right, 1, equal, right);
        root = merge(left, right);
    }
    void remove(size_t ql, size_t qr)
    {
        Node *left, *right, *equal;
        split(root, ql, left, right);
        split(right, qr - ql + 1, equal, right);
        root = merge(left, right);
    }
    void reverse(size_t ql, size_t qr)
    {
        Node *left, *right, *equal;
        split(root, ql, left, right);
        split(right, qr - ql + 1, equal, right);
        equal->reversed ^= 1;
        root = merge(merge(left, equal), right);
    }
    T get(size_t index)
    {
        Node *left, *right, *equal;
        split(root, index, left, right);
        split(right, 1, equal, right);
        T result = N_value(equal);
        root = merge(merge(left, equal), right);
        return result;
    }

    T get_min(size_t ql, size_t qr)
    {
        Node *left, *right, *equal;
        split(root, ql, left, right);
        split(right, qr - ql + 1, equal, right);
        T result = N_min(equal);
        root = merge(merge(left, equal), right);
        return result;
    }
};
template <typename T>
mt19937_64 cartesianTree<T>::rng64_t(chrono::steady_clock().now().time_since_epoch().count());

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<ll> a(n);
    cin >> a;
    cartesianTree<ll> tree(a);
    for (int i = 0; i < m; i++) {
        int c, l, r;
        cin >> c >> l >> r;
        if (c & 1) {
            tree.reverse(l - 1, r - 1);
        } else {
            cout << tree.get_min(l - 1, r - 1) << '\n';
        }
    }
}

int32_t main()
{
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
