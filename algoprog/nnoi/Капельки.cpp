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

bool comp(const pl&a, const pl&b){
    if (a.fi == b.fi) return a.se < b.se;
    return a.fi < b.fi;
}

vpl p;
ll n, d;
bool check(ll time){
    vpl segs;
    for (auto [x, t] : p){
        if (time > t){
            ll diff = time - t;
            segs.push_back({x - diff, x + diff});
        }
    }
    sort(all(segs), comp);
    bool start = 0;
    ll curright = -1;
    for (auto [f, s] : segs){
        if (f <= 0 && s >= 0) {
            start = 1;
            curright = s;
        }
        if (start && curright >= d) return 1;
        if (start) {
            if (f <= curright){
                curright = s;
            } else return 0;
        }
    }
    return curright >= d;
}

void solve() {
    cin >> n >> d;
    p.resize(n);
    for (int i = 0; i < n; i++) cin >> p[i].fi;
    for (int i = 0; i < n; i++) cin >> p[i].se;
    ll l = 0, r = 1e9 + 1;
    while (r - l > 1){
        ll m = (l + r) >> 1;
        if (check(m)){
            r = m;
        } else {
            l = m;
        }
    }
    cout << r;
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