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
    map<string, int> tshirts{{"S", 0}, {"M", 1}, {"L", 2}, {"XL", 3}, {"XXL", 4}, {"XXXL", 5}};
    map<int, string> tshirts_r{{0, "S"}, {1, "M"}, {2, "L"}, {3, "XL"}, {4, "XXL"}, {5, "XXXL"}};
    vi have(6);
    cin >> have;
    int n;
    cin >> n;
    vvi need(6);
    vi res(n, -1);
    for (int i = 0; i < n; i++){
        string s;
        cin >> s;
        string t;
        bool two = 0;
        for (auto j : s){
            if (j == ','){
                two = 1;
                need[tshirts[t]].push_back(i);
                t.clear();
                continue;
            }
            t += j;
        }
        if (!two && have[tshirts[t]]) have[tshirts[t]]--, res[i] = tshirts[t];
        else {
            need[tshirts[t]].push_back(i);
        }
    }
    for (int i = 0; i < 6; i++){
        while (have[i] && need[i].size()){
            res[need[i].back()] = i;
            have[i]--;
            need[i].pop_back();
        }
    }
    for (int i = 0; i < n; i++) if (res[i] == -1) return void (cout << "NO\n");
    cout << "YES\n";
    for (int i = 0; i < n; i++){
        cout << tshirts_r[res[i]] << "\n";
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