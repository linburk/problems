#include <bits/stdc++.h>
#include <climits>

using namespace std;

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<vi> vvi;
typedef vector<vl> vvl;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef vector<vvi> vvvi;
typedef vector<vvl> vvvl;
typedef vector<char> vc;
typedef vector<vc> vvc;
typedef pair<int, int> pi;
typedef pair<ll, ll> pl;
typedef vector<pi> vpi;
typedef vector<pl> vpl;
typedef vector<vpi> vvpi;
typedef vector<vpl> vvpl;

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
    //        os << "\n";
    return os;
}
} // namespace tools

using namespace tools;

class dsu{
    vi anc, rank;
public:
    int leader(int a){
        return (a == anc[a] ? a : anc[a] = leader(anc[a]));
    }
    void unite(int a, int b){
        a = leader(a), b = leader(b);
        if (rank[a] > rank[b]) swap(a, b);
        anc[a] = b;
        rank[b] = max(rank[b], rank[a] + 1);
    }
    dsu(int n){
        anc.resize(n); rank.resize(n);
        iota(all(anc), 0);
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    vi a(n);
    cin >> a;
    vi pos;
    dsu _d(n);
    for (int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        _d.unite(a - 1, b - 1);
    }
    map<int, vi> comps;
    for (int i = 0; i < n; i++){
        comps[_d.leader(i)].push_back(i);
    }
    for (auto [x, pos] : comps){
        vi elems;
        for (auto i : pos) elems.push_back(a[i]);
        sort(all(elems), greater<int>());
        for (int i = 0; i < pos.size(); i++){
            a[pos[i]] = elems[i];
        }
    }
    cout << a;
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
//    for (int i=0;i<t;i++)
    solve();
    return 0;
}