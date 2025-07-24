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
    int ind;
    int l, r;
};
int k;
int l = 0, r = -1;
vi cnt;
vi a;
int res = 0;
void oper(int i, bool op){
    if (cnt[a[i]] == k) res--;
    op ? cnt[a[i]]++ : cnt[a[i]]--;
    if (cnt[a[i]] == k) res++;
}

void solve() {
    int n, m, q;
    cin >> n >> m >> q >> k;
    a.resize(n);
    cin >> a;
    cnt.resize(m);
    vi ans(q);
    vector<query> queries(q);
    for (int i = 0; i < q; i++) cin >> queries[i].l >> queries[i].r, queries[i].ind = i, queries[i].l--;
    sort(all(queries), [](query &a, query &b){
        if (a.r == b.r) return a.l > b.l;
        return a.r > b.r;
    });
    for (auto &[ind, ql, qr] : queries){
        while (r < qr) oper(++r, 1);
        while (l < ql) oper(l++, 0);
        while (l > ql) oper(--l, 1);
        ans[ind] = res;
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