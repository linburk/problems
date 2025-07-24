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
    ld n, v;
    cin >> n >> v;
    vector<pair<ld, ld> > pupils(n);
    for (auto &[f, s] : pupils) cin >> f >> s;
    vector<pair<ld, int> > time(n);
    for (int i = 0; i < n; i++){
        time[i] = {pupils[i].first / pupils[i].second, i};
    }
    sort(all(time), greater<pair<ld, int> >());
    vector<pair<ld, int> > ans;
    ld current_time = 0;
    for (int i = 0; i < time.size(); i++){
        ld schooler_time = time[i].first; int index = time[i].second;
        if (current_time < schooler_time){
            ld ride_time = (pupils[index].first - current_time * pupils[index].second) / (pupils[index].second + v);
            ld distance = pupils[index].first - current_time * pupils[index].second - ride_time * pupils[index].second;
            current_time += ride_time + distance / v;
            ans.push_back({distance, index + 1});
        }
    }
    cout << fixed << setprecision(7) << current_time << ' ' << ans.size() << '\n';
    for (int i = 0; i < ans.size() && (cout << ans[i].second << " " << ans[i].first << "\n"); i++);
    
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