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

template<typename T, bool (*comparator)(T, T)>
class binary_heap{

    std::vector<T> tree;

    void sift_up(int node){
        while (node > 1 and comparator(tree[node], tree[node / 2])){
            swap(tree[node], tree[node / 2]);
            node /= 2;
        }
    }

    void sift_down(int node){
        while (node * 2 < tree.size()){
            int next = ((node * 2 + 1) < tree.size() and comparator(tree[node * 2 + 1], tree[node * 2]) ? node * 2 + 1 : node * 2);
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

    void insert(T x){
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

    void clear(){
        while (heap_size)
            pop();
    }

    T top(){
        return tree[1];
    }

    int size(){
        return heap_size;
    }

};


void solve(){
    auto comparator = [](pair<pair<int, int>, int> a, pair<pair<int, int>, int> b){
        if (a.first.first == b.first.first){
            if (a.first.second == b.first.second)
                return a.second < b.second;
            return a.first.second > b.first.second;
        }
        return a.first.first < b.first.first;
    };
    set<pair<pair<int, int>, int>, decltype(comparator)> events;
    int k, n;
    cin >> k >> n;
    int cnt = 0;
    for (int i = 0; i < n; i++){
        int whento, whenfrom;
        cin >> whento >> whenfrom;
        events.insert({{whento, 1}, i + 1});
        events.insert({{whenfrom, -1}, i + 1});
    }
    vector<int> ans(n);

    binary_heap<int, cmp_less> free;
    for (int i = 1; i <= k; i++)
        free.insert(i);
    map<int, int> employed;
    while (events.size()){
        int event = events.begin()->first.second;
        int ind = events.begin()->second;
//        cout << event << " " << ind << endl;
        if (event == 1){
            if (free.size() == 0){
                cout << "0 " << ind;
                exit(0);
            }
            ans[ind - 1] = free.top();
            employed[ind] = free.top();
            free.pop();
        }
        if (event == -1){
            free.insert(employed[ind]);
        }
        events.erase(events.begin());
    }
    cout << ans;
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