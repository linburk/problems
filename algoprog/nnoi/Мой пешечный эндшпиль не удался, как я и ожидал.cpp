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

#define fi first
#define se second
#define all(cont) cont.begin(), cont.end()
#define funique(cont) cont.erase(unique(all(cont)), cont.end())

namespace tools {
// mt19937_64 rng(chrono::steady_clock().now().time_since_epoch().count());
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

vector<vector<ll> > gr(2);
vvb used(2);

void dfs(ll i, ll j){
    if (used[i][j]) return;
    used[i][j] = 1;
    if (gr[i][j] != -1) dfs(i ^ 1, gr[i][j]);
}
void solve() {
    int n;
    cin >> n;
    vvl pieces(2);
    for (int i = 0; i < n; i++){
        ll c, r;
        cin >> c >> r;
        pieces[c - 1].push_back(r);
    }
    pieces[0].push_back(0);
    sort(all(pieces[0]));
    sort(all(pieces[1]));
    gr[0].resize(pieces[0].size(), -1);
    gr[1].resize(pieces[1].size(), -1);
    used[0].resize(pieces[0].size());
    used[1].resize(pieces[1].size());
    for (int i = 0; i < 2; i++){
        for (int j = 0; j < pieces[i].size(); j++){
            vl::iterator itnext = upper_bound(all(pieces[i ^ 1]), pieces[i][j]);
            if (itnext != pieces[i ^ 1].end()) gr[i][j] = distance(pieces[i ^ 1].begin(), itnext);;
        }
    }
    dfs(0, 0);
    if (used[0].size() && used[0][gr[0].size() - 1] || used[1].size() && used[1][gr[1].size() - 1]){
        cout << "YES";
    } else cout << "NO";
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
//    for (;t;t--)
    solve();
    return 0;
}