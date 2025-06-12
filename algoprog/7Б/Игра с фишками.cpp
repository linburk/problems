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

void solve() {
    int n;
    cin >> n;
    vector<int> cards(n);
    cin >> cards;
    sort(all(cards));
    ll p1 = 1, p2 = 1;
    for (int i = 0; i < n; i++){
        (i % 2 ? p1 += cards[i] : p2 += cards[i]);
    }
    cout << p1 << '\n' << p2;
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