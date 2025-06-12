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

class sqrt_d{
    const int BLOCK_SIZE = 555;
    vl add;
    vsl search;
    vvl blocks;
    vb changed;
    void rebuild(int pos){
        blocks[pos].clear();
        for (int j = pos * BLOCK_SIZE; j < arr.size() && j < (pos + 1) * BLOCK_SIZE; j++){
            blocks[pos].push_back(arr[j]);
        }
        sort(all(blocks[pos]));
    }
public:
    vl arr;
    sqrt_d(int n){
        arr.assign(n, 0);
        search.assign(n / BLOCK_SIZE + 1, sl{});
        changed.assign(n / BLOCK_SIZE + 1, 0);
        blocks.assign(n / BLOCK_SIZE + 1, vl{});
        add.assign(n / BLOCK_SIZE + 1, 0);
    }
    void initialize(void){
        for (int i = 0; i <= arr.size() / BLOCK_SIZE; i++){
            rebuild(i);
        }
    }
    void increment(int ql, int qr, ll x){
        for (; ql < qr && ql % BLOCK_SIZE != 0; ql++){
            int pos = ql / BLOCK_SIZE;
            arr[ql] += x;
            changed[pos] = 1;
        }
        for (; ql + BLOCK_SIZE < qr; ql += BLOCK_SIZE){
            int pos = ql / BLOCK_SIZE;
            add[pos] += x;
        }
        for (; ql < qr; ql++){
            int pos = ql / BLOCK_SIZE;
            arr[ql] += x;
            changed[pos] = 1;
        }
    }
    int get_lower(int ql, int qr, int x){
        int res = 0;
        for (; ql < qr && ql % BLOCK_SIZE != 0; ql++){
            int pos = ql / BLOCK_SIZE;
            res += (arr[ql] + add[pos]) < x;
        }
        for (; ql + BLOCK_SIZE < qr; ql += BLOCK_SIZE){
            int pos = ql / BLOCK_SIZE;
            if (changed[pos]) rebuild(pos);
            res += distance(blocks[pos].begin(), lower_bound(all(blocks[pos]), x - add[pos]));
        }
        for (; ql < qr; ql++){
            int pos = ql / BLOCK_SIZE;
            res += (arr[ql] + add[pos]) < x;
        }
        return res;
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    sqrt_d arr(n);
    cin >> arr.arr;
    arr.initialize();
    for (;q--;) {
        int comm, l, r, x;
        cin >> comm >> l >> r >> x; l--;
        if (comm == 1){
            cout << arr.get_lower(l, r, x) << "\n";
        }
        if (comm == 2){
            arr.increment(l, r, x);
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