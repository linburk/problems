#include <bits/stdc++.h>
using namespace std;

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

#define endl '\n'
#define all(cont) cont.begin(), cont.end()
#define unique(cont) cont.erase(unique(all(cont)), cont.end())

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

class _DSU{
public:
    _DSU(){}
    _DSU(int n){
        reset(n);
    }
    void reset(int n){
        rank.resize(n, 1);
        ancestor.resize(n);
        iota(ancestor.begin(), ancestor.end(), 0);
    }
    void unite(int a, int b){
        a = leader(a); b = leader(b);
        if (rank[a] > rank[b]) swap(a, b);
        ancestor[a] = b;
        rank[b] = max(rank[b], rank[a] + 1);
    }
    int leader(int v){
        return (v == ancestor[v] ? v : ancestor[v] = leader(ancestor[v])); // ÑÑÐ¾-ÑÐ¾ Ð½Ðµ ÑÑÐ°Ð·Ñ Ð·Ð°Ð¼ÐµÑÐ¸Ð», ÑÑÐ¾ Ð¿ÑÐµÐ´ÐºÐ¾Ð² Ð½Ðµ Ð¼ÐµÐ½ÑÐ»
    }
private:
    vector<int> ancestor, rank;
};
struct edge{
    int a, b, w;
};
class _fMST : public _DSU{
public:
    vector<int> operator()(vector<edge> &edges, int n){
        reset(n);
        findMST(edges);
        return MST;
    }
protected:
    vector<int> MST;
private:
    void findMST(vector<edge> &edges){
        for (int i = 0; i < edges.size(); i++){
            auto [a, b, w] = edges[i];
            if (leader(a) != leader(b)){
                MST.push_back(i);
                unite(a, b);
            }
        }
    }
};

void solve(){
    int n, m;
    cin >> n >> m;
    vector<edge> edges;
    for (int i = 0; i < m; i++){
        int a, b, w;
        cin >> a >> b >> w;
        edges.push_back({a - 1, b - 1, w});
    }
    auto comp = [](const edge& a, const edge& b){
        return a.w < b.w;
    };
    sort(all(edges), comp);
    _fMST fMST;
    vector<int> mst = fMST(edges, n);
    int ans = -1e9;
    for (auto i : mst){
        ans = max(ans, edges[i].w);
    }
    cout << ans;
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