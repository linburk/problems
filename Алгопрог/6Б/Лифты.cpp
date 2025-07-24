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

template<typename T, bool (*comparator)(const T, const T)>
class binary_heap{
    std::vector<T> tree;
    void sift_up(size_t node){
        while (node > 1 and comparator(tree[node], tree[node / 2])){
            swap(tree[node], tree[node / 2]);
            node /= 2;
        }
    }
    void sift_down(size_t node){
        size_t maxindex = node;
        for (size_t son = 2 * node; son <= 2 * node + 1; son++){
            if (son < tree.size() && tree[son] > tree[maxindex])
                maxindex = son;
        }
        if (maxindex == node)
            return;
        swap(tree[maxindex], tree[node]);
        sift_down(maxindex);
    }
    size_t heap_size = 0;
public:
    binary_heap(){
        tree.reserve(1E6 + 1);
        tree.resize(1);
    }
    void push(T x) {
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
    const bool empty(){
        return heap_size == 0;
    }

};

struct comp{
    const bool operator()(pair<int, int> a, pair<int, int> b) {
        return a.first < b.first;
    }
};

void dijkstra(vector<vector<pair<int, int> > > &gr, int n){
    set<pair<int, int>> q;
//    binary_heap<pair<int, int>, cmp> q;
    vector<int> dist(1E6 + 1, 1E9);
    dist[1] = 0;
    q.insert({dist[1], 1});
    while (!q.empty()){
        auto [d, from] = *q.begin();
        q.erase(q.begin());
        if (d > dist[from])
            continue;
        for (auto [to, weight] : gr[from]){
            if (dist[to] > dist[from] + weight) {
                q.erase({dist[to], to});
                dist[to] = dist[from] + weight;
                q.insert({dist[to], to});
            }
        }
    }
    cout << dist[n];
}

void solve() {
    int n, up, down, to_lift, from_lift, lift_num;
    cin >> n >> up >> down >> to_lift >> from_lift >> lift_num;
    vector<int> vertexes;
    vertexes.push_back(1);
    vertexes.push_back(n);
    vector<vector<pair<int, int> > > gr(1E6 + 1);
    for (int k, i = 0; i < lift_num; i++) {
        cin >> k;
        vector<int> lift(k);
        cin >> lift;
        for (int j = 0; j < k; j++){
            vertexes.push_back(lift[j]);
            for (int m = j + 1; m < k; m++){
                gr[lift[j]].push_back({lift[m], to_lift + from_lift});
                gr[lift[m]].push_back({lift[j], to_lift + from_lift});
            }
        }
    }
    sort(all(vertexes));
    for (int i = 0; i < vertexes.size() - 1; i++) {
        int floor_cur = vertexes[i], floor_next = vertexes[i + 1];
        gr[floor_cur].push_back({floor_next, (floor_next - floor_cur) * up});
        gr[floor_next].push_back({floor_cur, (floor_next - floor_cur) * down});
    }
    dijkstra(gr, n);
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