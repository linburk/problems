#include <bits/stdc++.h>
#include <climits>

#define all(cont) cont.begin(), cont.end()
#define funique(cont) cont.erase(unique(all(cont)), cont.end())

namespace {
using ll = std::int64_t;
using ull = std::uint64_t;
using uint = std::uint64_t;
using ld = long double;
using pi = std::pair<int, int>;
using pl = std::pair<ll, ll>;
using pul = std::pair<ull, ull>;
using vi = std::vector<int>;
using vl = std::vector<ll>;
using vb = std::vector<bool>;
using vc = std::vector<char>;
using vpi = std::vector<pi>;
using vpl = std::vector<pl>;
using vvi = std::vector<vi>;
using vvl = std::vector<vl>;
using vvb = std::vector<vb>;
using vvc = std::vector<vc>;
using vvpi = std::vector<vpi>;
using vvpl = std::vector<vpl>;
using si = std::set<int>;
using sl = std::set<ll>;
using spi = std::set<pi>;
using spl = std::set<pl>;
using mi = std::map<int, int>;
using ml = std::map<ll, ll>;
using umi = std::unordered_map<int, int>;
using uml = std::unordered_map<ll, ll>;
}

namespace {
std::mt19937_64 rng(std::chrono::steady_clock().now().time_since_epoch().count());
void debug(auto&&... Args) {
    ((std::cout << Args << " "), ...);
    std::cout << "\n";
};
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
}

using std::cin, std::cout;

void solve() {
    std::string a, b;
    cin >> a >> b;
    a = " " + a, b = " " + b;
    int n = (int)a.size(), m = (int)b.size();
    vvi dp(n, vi(m, 1e9));
    vvpi past(n, vpi(m, std::make_pair(-1, -1)));
    vvc add(n, vc(m));
    dp[0][0] = 0;
    for (int i = 1; i < n; ++i) {
        for (int j = 1; j < m; ++j) {
            if (a[i] != '*' && b[j] != '*') {
                if (not (a[i] != b[j] && a[i] != '?' && b[j] != '?')){
                    past[i][j] = {i - 1, j - 1};
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                    add[i][j] = (a[i] == '?' && b[j] == '?' ? 'A' : (b[j] == '?' ? a[i] : b[j]));
                }
            } else if (a[i] == '*' && b[j] == '*') {
                (dp[i - 1][j] <= dp[i - 1][j - 1] && dp[i - 1][j] <= dp[i][j - 1] ? past[i][j] = {i, j - 1} :  std::make_pair(0, 0));
                (dp[i][j - 1] <= dp[i - 1][j - 1] && dp[i][j - 1] <= dp[i - 1][j] ? past[i][j] = {i, j - 1} :  std::make_pair(0, 0));
                (dp[i - 1][j - 1] <= dp[i - 1][j] && dp[i - 1][j - 1] <= dp[i][j - 1] ? past[i][j] = {i, j - 1} :  std::make_pair(0, 0));
                dp[i][j] = std::min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
            } else if (a[i] == '*') {
                (dp[i - 1][j] < dp[i - 1][j - 1] ? past[i][j] = {i, j - 1} : past[i][j] = {i - 1, j - 1});
                dp[i][j] = std::min({dp[i - 1][j], dp[i - 1][j - 1]}) + 1;
                add[i][j] = (b[j] == '?' ? 'A' : b[j]);
            } else if (b[j] == '*') {
                (dp[i][j - 1] < dp[i - 1][j - 1] ? past[i][j] = {i, j - 1} : past[i][j] = {i - 1, j - 1});
                dp[i][j] = std::min({dp[i][j - 1], dp[i - 1][j - 1]}) + 1;
                add[i][j] = (a[i] == '?' ? 'A' : a[i]);
            }
        }
    }
    if (dp[n - 1][m - 1] == 1e9) {
        cout << "No solution\n";
        return;
    }
    std::string result;
    int px = n - 1, py = m - 1;
    while (px != -1 && py != -1) {
        if (add[px][py]) result += add[px][py];
        auto next = past[px][py];
        px = next.first, py = next.second;
    }
    std::reverse(all(result));
    cout << result << "\n";
}

int32_t main() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
    setlocale(LC_ALL, "Russian");
#ifdef __APPLE__
    std::freopen("/Users/dmitrii/Documents/Code/Code/input.txt", "r", stdin);
    std::freopen("/Users/dmitrii/Documents/Code/Code/output.txt", "w", stdout);
#endif
//    int t;
//    std::cin >> t;
//    for (int i = 0; i < t; i++)
        solve();
    return 0;
}