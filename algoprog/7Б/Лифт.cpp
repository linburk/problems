#include <bits/stdc++.h>
using namespace std;
 
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
 
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
        os << "\n";
        return os;
    }
    template <typename T, typename V>
    std::istream &operator>>(std::istream &is, std::pair<T, V> &p) {
        is >> p.first >> p.second;
        return is;
    }
}  // namespace tools
 
using namespace tools;

ll n, c, p, t;
vector<ll> a;
ll check(ll floor){
    vector<ll> a_c = a;
    ll t_c = t;
    ll cnt = 0;
    while (1){
        bool max_fl = 0;
        ll in_lift = 0;
        for (int i = floor; i >= 1; i--){
            if (a_c[i]){
                if (!max_fl){
                    max_fl = 1;
                    t_c -= i * p;
                }
                ll pass = min(a_c[i], c - in_lift);
                a_c[i] -= pass;
                in_lift += pass;
            }
            if (max_fl) t_c -= p;
        }
        cnt += in_lift;
        if (!max_fl) break;
    }
    return (t_c < 0 ? 0 : cnt);
}
void solve() {
    cin >> n >> c >> p >> t;
    a.resize(n + 1);
    for (int i = 1; i <= n && cin >> a[i]; i++);
    vector<int> can(n + 1, 0);
    for (ll i = 1; i <= n; i++){
        can[i] = check(i);
    }
//    cout << can << '\n';
    ll maxr = -1;
    ll maxi = -1;
    for (int i = 1; i <= n; i++){
        if (can[i] > maxr){
            maxr = can[i]; maxi = i;
        }
    }
    if (maxi + 1 <= n){
        ll l = -1, r = a[maxi + 1];
        while (r - l > 1){
            ll m = (l + r) >> 1;
            a[maxi + 1] = m;
            if (check(maxi + 1) >= maxr){
                l = m;
            } else {
                r = m;
            }
        }
        a[maxi + 1] = l;
        cout << check(maxi + 1);
    } else
        cout << check(maxi);
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