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

class staticLCA{
    vector<int> depth;
    vector<vector<int> > binUps;
    vector<vector<bool> > funCanTo, funCanFrom;
    void dfs(map<pair<int, int>, bool> &path, vector<vector<int> > &gr, int v, int past){
        depth[v] = depth[past] + 1;
        binUps[v][0] = past;
        funCanTo[v][0] = path[{past, v}];
        funCanFrom[v][0] = path[{v, past}];
        for (int i = 1; i < 30; i++){
            binUps[v][i] = binUps[binUps[v][i - 1]][i - 1];
            funCanTo[v][i] = funCanTo[v][i - 1] & funCanTo[binUps[v][i - 1]][i - 1];
            funCanFrom[v][i] = funCanFrom[v][i - 1] & funCanFrom[binUps[v][i - 1]][i - 1];
        }
        for (auto to : gr[v]) if (to != past) dfs(path, gr, to, v);
    }
    void build(map<pair<int, int>, bool> &path, vector<vector<int> > &gr, int root){
        depth.resize(gr.size());
        binUps.resize(gr.size(), vector<int>(30));
        funCanTo.resize(gr.size(), vector<bool>(30));
        funCanFrom.resize(gr.size(), vector<bool>(30));
        depth[root] = -1;
        dfs(path, gr, root, root);
    }
public:
    staticLCA(){}
    
    staticLCA(map<pair<int, int>, bool> &path, vector<vector<int> > &gr, int root){
        build(path, gr, root);
    }
    
    bool check_path(int a, int b){
        bool ans = 1;
        if (depth[a] < depth[b]){
            for (int i = 29; i >= 0; i--){
                if (depth[binUps[b][i]] >= depth[a]){
                    ans = funCanTo[b][i] & ans;
                    b = binUps[b][i];
                }
            }
        } else {
            for (int i = 29; i >= 0; i--){
                if (depth[binUps[a][i]] >= depth[b]){
                    ans = funCanFrom[a][i] & ans;
                    a = binUps[a][i];
                }
            }
        }
        if (a == b || !ans) return ans;
        for (int i = 29; i >= 0; i--){
            if (binUps[a][i] != binUps[b][i]){
                ans = ans & funCanTo[b][i] & funCanFrom[a][i];
                a = binUps[a][i];
                b = binUps[b][i];
            }
        }
        return ans & funCanTo[b][0] & funCanFrom[a][0];
    }
};


void solve() {
    int n;
    cin >> n;
    map<pair<int, int>, bool> can;
    vector<vector<int> > gr(n);
    int root;
    for (int i = 1; i < n; i++){
        int a, b;
        cin >> a >> b;
        gr[a - 1].push_back(b - 1);
        gr[b - 1].push_back(a - 1);
        can[{a - 1, b - 1}] = 1;
    }
    can[{0, 0}] = 1;
    staticLCA LCA(can, gr, 0);
    int m;
    cin >> m;
    for (int i = 0; i < m; i++){
        int x, y;
        cin >> x >> y;
        cout << (LCA.check_path(x - 1, y - 1) ? "Yes" : "No") << endl;
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