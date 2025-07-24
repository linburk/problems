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
typedef map<int, int> mi;
typedef map<ll, ll> ml;
typedef vector<mi> vmi;
typedef vector<ml> vml;
typedef set<int> si;
typedef set<ll> sl;
typedef vector<si> vsi;
typedef vector<sl> vsl;
typedef unordered_map<int, int> umi;
typedef unordered_map<ll, ll> uml;

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

struct query{
    int ind, l, r;
};

void solve() {
    int n, m;
    cin >> n >> m;
    vi a(n);
    cin >> a;
    vector<query> queries(m);
    vi ans(m);
    for (int i = 0;  i < m; i++) cin >> queries[i].l >> queries[i].r, queries[i].ind = i, queries[i].l--, queries[i].r--;
    const int BLOCK_SIZE = 555;
    vvi blocks(n / BLOCK_SIZE + 1);
    for (auto &[ind, l, r] : queries) blocks[l / BLOCK_SIZE].push_back(ind);
    for (int i = 0; i < blocks.size(); i++) sort(all(blocks[i]), [&queries](int a, int b){
        return queries[a].r < queries[b].r;
    });
    vi count(n + 2);
    int res = 0;
    auto oper = [&count, &res, &a](int i, bool op){
        if (count[a[i]] == a[i]) res--;
        op ? count[a[i]]++ : count[a[i]]--;
        if (count[a[i]] == a[i]) res++;
    };
    for (int l = 0, r = -1, i = 0; i < blocks.size(); i++){
        if (blocks[i].empty()) continue;
        for (int j = l; j <= r; j++) count[(a[j] > n ? n + 1 : a[j])] = 0;
        l = i * BLOCK_SIZE, r = queries[blocks[i][0]].r;
        for (int j = l; j <= r; j++) oper(j, 1);
        for (int j = 0; j < blocks[i].size(); j++){
            int ind = blocks[i][j];
            for (; r < queries[ind].r; ) oper(++r, 1);
            for (; l > queries[ind].l; ) oper(--l, 1);
            for (; l < queries[ind].l; ) oper(l++, 0);
            ans[ind] = res;
        }
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
//    for (int i=0;i<t;i++)
    solve();
    return 0;
}