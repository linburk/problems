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
vector<vector<int> > A(13, vector<int>(13, 1));
vector<int> fact(13);
ll get_number(vector<int> &a, int n, int k){
    ll num = 0;
    list<int> perm(n);
    iota(all(perm), 1);
    n--; k--;
    for (int i = 0; i < a.size(); i++){
        int j = 0;
        for (auto it = perm.begin(); it != perm.end(); it++, j++){
            if (*it == a[i]){
                num += j * A[n][k];
                perm.erase(it);
                break;
            }
        }
        n--; k--;
    }
    return num;
}
void solve() {
    fact[0] = 1;
    for (int i = 1; i < 13; i++) fact[i] = fact[i - 1] * i;
    for (int i = 0; i < 13; i++){
        for (int j = 0; j <= i; j++){
            A[i][j] = fact[i] / fact[i - j];
        }
    }
    int n, k;
    cin >> n >> k;
    vector<int> a(k);
    cin >> a;
    cout << get_number(a, n, k) + 1;
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