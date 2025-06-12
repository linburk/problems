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

vi z_func(vi &s){
    vi z(s.size() + 1);
    for (int l = 0, r = 0, i = 1; i < s.size(); i++){
        if (i < r) z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < s.size() && (s[z[i]] == s[i + z[i]] || (s[z[i]] == 1e9 && z[i] - s[i + z[i]] + 1 < 0))) z[i]++;
        if (i + z[i] - 1 > r) r = i + z[i] - 1, l = i;
    }
    return z;
}
void solve() {
    string t, p;
    cin >> t >> p;
    vi lett(26, 1e9), letp(26, 1e9);
    vi newt(t.size()), newp(p.size() + 1, -1);
    for (int i = 0; i < t.size(); i++){
        if (lett[t[i] - 'a'] == 1e9) newt[i] = 1e9;
        else newt[i] = i - lett[t[i] - 'a'] + 1;
        lett[t[i] - 'a'] = i;
    }
    for (int i = 0; i < p.size(); i++){
        if (letp[p[i] - 'a'] == 1e9) newp[i] = 1e9;
        else newp[i] = i - letp[p[i] - 'a'] + 1;
        letp[p[i] - 'a'] = i;
    }
    vi newtp = newp;
    newtp.insert(newtp.end(), all(newt));
    vi z = z_func(newtp);
    vi ans;
    for (int i = p.size() + 1; i < z.size(); i++){
        if (z[i] == p.size()) ans.push_back(i - p.size());
    }
    cout << ans.size() << "\n" << ans;
    
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