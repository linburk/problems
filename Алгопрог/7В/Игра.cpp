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

void solve() {
    
    int n, m;
    cin >> n >> m;
    vector<pair<int, pi> > pocket(n), chest(m);
    for (int i = 0; i < n; i++) cin >> pocket[i].first, pocket[i].second.first = i, pocket[i].second.second = 1;
    for (int i = 0; i < m; i++) cin >> chest[i].first, chest[i].second.first = i, chest[i].second.second = 2;
    multiset<pair<int, pi> > pac;
    pac.insert(pocket.begin(), pocket.end());
    pac.insert(chest.begin(), chest.end());
    vi drop, get;
    auto it = prev(pac.end());
    for (int i = 0; i < n; i++) {
        if (it->second.second == 2){
            get.push_back(it->second.first);
        }
        it--;
    }
    for (int i = 0; i < m; i++){
        it--;
        if (it->second.second == 1){
            drop.push_back(it->second.first);
        }
    }
    cout << get.size() << "\n";
    for (int i = 0; i < get.size(); i++){
        cout << drop[i] + 1 << " " << get[i] + 1 << "\n";
    }
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