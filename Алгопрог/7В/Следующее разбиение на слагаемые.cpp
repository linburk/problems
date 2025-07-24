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

void next_permutation(vi &a){
    int i = a.size() - 2, j = a.size() - 1;
    a[i]++;
    a[j]--;
    if (a[i] > a[j]){
        a[i] += a[j];
        a.erase(a.begin() + j);
    }
    else {
        while (a[i] * 2 <= a[j]){
            int t = a[j] - a[i];
            a[i] = a[i - 1];
            a.push_back(t);
            
        }
    }
}

void solve() {
    string s;
    cin >> s;
    vi a;
    int num = 0;
    for (int i = 0; i < s.size(); i++){
        string t;
        while (i < s.size() && isdigit(s[i])){
            t += s[i], i++;
        }
        if (t.size()) a.push_back(stoi(t));
    }
    num = a[0];
    a.erase(a.begin());
    if (a.size()) next_permutation(a);
    else return void(cout << "NO SOLUTION\n");
    cout << num << "=";
    for (int i = 0; i < a.size(); i++) cout << a[i] << "+\n"[i == a.size() - 1];
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