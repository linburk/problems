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

vi z_f(vi &a){
    vi z(a.size() + 1);
    for (int l = 0, r = 0, i = 1; i < a.size(); i++){
        if (i <= r) z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < a.size() && a[z[i]] == a[i + z[i]]) z[i]++;
        if (i + z[i] - 1 > r) r = i + z[i] - 1, l = i;
    }
    return z;
}

void solve() {
    int n;
    cin >> n;
    vi dels;
    for (int i = 1; i * i < n; i++){
        if ((n - 1) % i == 0){
            dels.push_back((n - 1) / i);
            dels.push_back(i);
        }
    }
    sort(all(dels));
    vi a(n);
    cin >> a;
    a.pop_back();
    for (auto j : dels){
        vi at;
        at.insert(at.end(), a.begin(), a.begin() + j);
        at.push_back(-1);
        at.insert(at.end(), all(a));
        vi z_i = z_f(at);
        if (z_i[z_i.size() - j - 1] == j) return void(cout << j);
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