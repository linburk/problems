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

template<typename T, bool (*comparator)(const T&, const T&)>
class sparseTable{
    std::vector<std::vector<T> > ST;
    void build(const std::vector<T> &arr) {
        ST.resize(32 - __builtin_clz(arr.size() + 1), std::vector<T>(arr.size()));
        ST[0] = arr;
        for (int i = 0; i + 1 < 32 - __builtin_clz(arr.size() + 1); i++) {
            for (int j = 0; j < arr.size() - (1 << i); j++) {
                ST[i + 1][j] = (comparator(ST[i][j], ST[i][j + (1 << i)]) ? ST[i][j] : ST[i][j + (1 << i)]);
            }
        }
    }

public:
    sparseTable(){}

    sparseTable(const std::vector<T> &arr){
        build(arr);
    }

    const T get(int l, int r){
        int d = 31 - __builtin_clz(r - l);
        return (comparator(ST[d][l], ST[d][r - (1 << d)]) ? ST[d][l] : ST[d][r - (1 << d)]);
    }
    const int size(){
        return ST[0].size();
    }

    void operator()(std::vector<T> &arr){
        build(arr);
    }
};


class staticLCA{
    inline static bool comp(const pair<int, int>& a, const pair<int, int>& b){
        return (a.first < b.first ? 1 : 0);
    }
    // vector<int> tin, tout;
    vector<pair<int, int> > euler_tour;
    vector<int> first_enter, last_enter;
    // int time = 0;
    
    sparseTable<pair<int, int>, comp> RMQ;

    void dfs(vector<vector<int> > &gr, int v, int depth){
        // tin[v] = time++;
        first_enter[v] = euler_tour.size();
        euler_tour.push_back(make_pair(depth, v));
        for (auto to : gr[v]){
            dfs(gr, to, depth + 1);
            euler_tour.push_back(make_pair(depth, v));
        }
        last_enter[v] = euler_tour.size();
        // tout[v] = time++;
    }

    void build(vector<vector<int> > &graph, int root){
        // tin.resize(graph.size());
        // tout.resize(graph.size());
        first_enter.resize(graph.size());
        last_enter.resize(graph.size());
        dfs(graph, root, 0);
        RMQ(euler_tour);
    }

public:
    staticLCA(vector<vector<int> > &graph, int root){
        build(graph, root);
    }

    int get(int u, int v){
        return RMQ.get(min(first_enter[u], first_enter[v]), max(last_enter[u], last_enter[v])).second;
    }

    // bool is_ancestor(int _anc, int v){
    //     return tin[_anc] < tin[v] && tin[v] < tout[v] && tout[v] < tout[_anc];
    // }
 
};



void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<int> > graph(n);
    for (int i = 1; i < n; i++){
        int v;
        cin >> v;
        graph[v].push_back(i);
    }
    staticLCA LCA(graph, 0);
    ll x, y, z;
    vector<ll> a(2 * m + 1);
    cin >> a[1] >> a[2] >> x >> y >> z;
    for (int i = 3; i <= 2 * m; i++){
        a[i] = (x * a[i - 2] + y * a[i - 1] + z) % n;
    }
    ll a1 = a[1], a2 = a[2]; 
    ll cnt = 0;
    for (int i = 2; i <= m + 1; i++){
        ll ans = LCA.get(a1, a2);
        // cout << a1 + 1 << " " << a2 + 1 << " " << ans + 1 << endl;
        cnt += 1ll * ans;
        a1 = (a[2 * i - 1] + ans) % n;
        a2 = a[2 * i];
    }
    cout << cnt;
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