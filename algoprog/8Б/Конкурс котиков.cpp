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
typedef pair<ull, ull> pull;

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
//            os << "\n";
    return os;
}
} // namespace tools

using namespace tools;

int n, m;
vvi gr;
vvi rev_gr;

vi order;
vb used;
vi member;
int css_size = 0;
void topsort(int v){
    used[v] = 1;
    for (auto to : gr[v]) if (!used[to]) topsort(to);
    order.push_back(v);
}
void condensate(int v){
    member[v] = css_size;
    for (auto to : rev_gr[v]) if (member[to] == -1) condensate(to);
}
void solve() {
    cin >> n >> m;
    gr.assign(n, vi{});
    rev_gr.assign(n, vi{});
    for (int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        a--, b--;
        gr[a].push_back(b);
        rev_gr[b].push_back(a);
    } used.assign(n, 0); member.assign(n, -1); order.clear(); css_size = 0;
    for (int i = 0; i < n; i++) if (!used[i]) topsort(i);
    for (int i = n - 1; i >= 0; i--){
        if (member[i] == -1) condensate(i), css_size++;
    }
    if (css_size == 1) cout << "No\n";
    else {
        vi c, h;
        for (int i = 0; i < n; i++){
            if (member[i] == css_size - 1){
                c.push_back(i + 1);
            } else {
                h.push_back(i + 1);
            }
        }
        cout << "Yes\n" << c.size() << " " << h.size() << "\n" << c << "\n" << h << "\n";
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
    int t;
    cin >> t;
    for (int i = 0; i < t; i++)
        solve();
    return 0;
}