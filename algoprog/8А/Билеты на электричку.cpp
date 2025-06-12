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

void solve() {
    int n, k, m;
    cin >> n >> k >> m;
    const int BLOCK_SIZE = 555;
    vi arr(n);
    vi blocks(n / BLOCK_SIZE + 1);
    vi added(n / BLOCK_SIZE + 1);
    auto add = [&](int l, int r){
        for (; l < r && l % BLOCK_SIZE != 0; l++) { arr[l]++; blocks[l / BLOCK_SIZE] = max(blocks[l / BLOCK_SIZE], arr[l]); }
        for (; l + BLOCK_SIZE < r; l += BLOCK_SIZE) added[l / BLOCK_SIZE]++;
        for (; l < r; l++) { arr[l]++; blocks[l / BLOCK_SIZE] = max(blocks[l / BLOCK_SIZE], arr[l]); }
    };
    auto max_q = [&](int l, int r){
        int res = 0;
        for (; l < r && l % BLOCK_SIZE != 0; l++) res = max(res, arr[l] + added[l / BLOCK_SIZE]);
        for (; l + BLOCK_SIZE < r; l += BLOCK_SIZE) res = max(res, added[l / BLOCK_SIZE] + blocks[l / BLOCK_SIZE]);
        for (; l < r; l++) res = max(res, arr[l] + added[l / BLOCK_SIZE]);
        return res;
    };
    for (int i = 0; i < m; i++){
        int x, y;
        cin >> x >> y;
        if (max_q(x, y) < k){
            cout << "1\n";
            add(x, y);
        } else {
            cout << "0\n";
        }
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