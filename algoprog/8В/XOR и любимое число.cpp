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
    int l, r, ind;
};
const int BLOCK_SIZE = 555;
int k;
vi a(1e5 + 1);
vi ans(1e5 + 1);
vi prefxor(1e5 + 2);
vi cnt(1e6 + 1);
vi cntl(1e6 + 1), cntr(1e6 + 1);
vvi blocks(1e5 / BLOCK_SIZE + 1);
vector<query> queries(1e5 + 1);
int res;
int res2;
void oper(int pos, bool op){
    if (!op){
        res -= cnt[prefxor[pos] ^ k];
        cnt[prefxor[pos]]--;
    } else {
        res += cnt[prefxor[pos] ^ k];
        cnt[prefxor[pos]]++;
    }
}
void solve() {
    int n, m;
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) prefxor[i + 1] = prefxor[i] ^ a[i];
    for (int i = 0; i < m; i++) cin >> queries[i].l >> queries[i].r, queries[i].ind = i, queries[i].l--;
    for (int i = 0; i < m; i++) blocks[queries[i].l / BLOCK_SIZE].push_back(i);
    for (int i = 0; i < n / BLOCK_SIZE + 1; i++)
        sort(all(blocks[i]),
             [&](int a, int b){return queries[a].r < queries[b].r;});
    for (int i = 0, l = -1, r = 0; i < n / BLOCK_SIZE + 1; i++){
        if (blocks[i].empty()) continue;
        res2 = res = 0;
        for (int j = max(0, (i - 1) * BLOCK_SIZE); j <= min(r + 1, n - 1); j++) cnt[prefxor[j]] = 0, cntl[prefxor[j]] = cntr[prefxor[j]] = 0;
        l = i * BLOCK_SIZE, r = queries[blocks[0][0]].r;
        for (int j = l; j <= r; j++) oper(j, 1);
        for (auto ind : blocks[i]){
            for (; l < queries[ind].l; ) oper(l++, 0);
            for (; l > queries[ind].l; ) oper(--l, 1);
            for (; r < queries[ind].r; ) oper(++r, 1);
            ans[queries[ind].ind] = res;
        }
    }
    for (int i = 0; i < m; i++) cout << ans[i] << " ";
    for (int i = 0; i < n / BLOCK_SIZE + 1; i++) blocks[i].clear();
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