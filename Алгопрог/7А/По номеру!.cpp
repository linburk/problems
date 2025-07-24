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
        return os;
    }
    template <typename T, typename V>
    std::istream &operator>>(std::istream &is, std::pair<T, V> &p) {
        is >> p.first >> p.second;
        return is;
    }
}  // namespace tools
 
using namespace tools;
vector<ll> fact(13);

void get_permutation(ll n, ll k){
    vector<int> perm(n + 1);
    vector<bool> used(n + 1);
    for (int i = 1; i <= n; i++){
        ll alr = k / fact[n - i];
        k %= fact[n - i];
        ll free = 0;
        for (int j = 1; j <= n; j++){
            if (!used[j]){
                free++;
                if (free == alr + 1){
                    perm[i] = j;
                    used[j] = 1;
                }
            }
        }
    }
    for (int i = 1; i <= n; i++) cout << perm[i] << " ";
}

void solve() {
    fact[0] = 1;
    for (int i = 1; i < 12; i++){
        fact[i] = fact[i - 1] * i;
    }
    ll n, k;
    cin >> n >> k;
    get_permutation(n, k - 1);
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