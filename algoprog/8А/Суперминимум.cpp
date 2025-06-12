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

class sqrt_decompose{
    const int BLOCK_SIZE = 500;
    vi block;
public:
    vi arr;
    sqrt_decompose(int n){
        arr.resize(n);
        block.resize(n / BLOCK_SIZE + 1, INT_MAX);
    }
    void initialize(void){
        for (int i = 0; i < arr.size(); i++){
            block[i / BLOCK_SIZE] = min(block[i / BLOCK_SIZE], arr[i]);
        }
    }
    int get_min(int ql, int qr){
        int res = INT_MAX;
        for (; ql < qr && ql % BLOCK_SIZE != 0; ql++){
            res = min(arr[ql], res);
        }
        for (; ql + BLOCK_SIZE < qr; ql += BLOCK_SIZE){
            res = min(block[ql / BLOCK_SIZE], res);
        }
        for (; ql < qr; ql++){
            res = min(arr[ql], res);
        }
        return res;
    }
};



void solve() {
    int n, k;
    cin >> n >> k;
    sqrt_decompose arr(n);
    cin >> arr.arr;
    arr.initialize();
    for (int i = 0; i < n - k; i++){
        cout << arr.get_min(i, i + k) << " ";
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