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
//        os << "\n";
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
    int m;
    cin >> m;
    vector<pair<pair<int, int>, int> > segms;
    for (int i = 0, l = -1, r = -1; cin >> l >> r && !(l == 0 && r == 0); i++) {
        segms.push_back({{l, r}, i});
    }
    sort(all(segms), [](pair<pair<int, int>, int> &a, pair<pair<int, int>, int> &b) -> bool {
        return a.first.first == b.first.first ? a.first.second < b.first.second : a.first.first < b.first.first;
    });
    int curleft = 0;
    vector<int> ans;
    set<pair<int, int> > right;
    right.insert({-1e9, -1e9});
    for (int i = 0; true; i++) {
    if (curleft >= m) break;
    if (i < segms.size() && segms[i].first.first <= curleft) {
        right.insert({segms[i].first.second, i});
        continue;
    }
    auto [rmax, maxind] = *right.rbegin();
    if (rmax > curleft) {
            curleft = rmax;
            ans.push_back(maxind);
            i--;
            continue;
    }
    if (rmax <= curleft) break;
    }
    if (curleft < m) {
        cout << "No solution";
        exit(0);
    }
    cout << ans.size() << endl;
    for (auto k : ans) {
        auto [segm, ind] = segms[k];
        auto [l, r] = segm;
        cout << l << " " << r << endl;
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
//    for (int i = 0; i < t; i++)
    solve();
    return 0;
}