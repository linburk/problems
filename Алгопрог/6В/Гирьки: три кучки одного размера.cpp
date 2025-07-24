#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

#define endl '\n'
#define all(cont) cont.begin(), cont.end()
#define unique(cont) cont.erase(unique(all(cont)), cont.end())
#define pb(x) emplace_back(x)

namespace tools {

    template <typename T>
    T gcd(T a, T b) {
        while (b > 0) {
            a %= b;
            std::swap(a, b);
        }
        return a;
    }

    template <typename T>
    T lcm(T a, T b) {
        return a * b / gcd(a, b);
    }

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
        return os;
    }

    template <typename T>
    std::istream &operator>>(std::istream &is,
                             std::vector<std::vector<T> > &matrix) {
        for (auto &i : matrix)
            for (auto &j : i) is >> j;
        return is;
    }

    template <typename T>
    std::ostream &operator<<(std::ostream &os,
                             const std::vector<std::vector<T> > &matrix) {
        for (const auto &i : matrix) {
            for (const auto &j : i) os << j << " ";
            os << "\n";
        }
        return os;
    }

    template <typename T, typename V>
    std::istream &operator>>(std::istream &is, std::pair<T, V> &p) {
        is >> p.first >> p.second;
        return is;
    }

}  // namespace tools
using namespace tools;


vector<int> gires;
vector<bool> used;
vector<vector<bool> > usedn(3);
vector<vector<int> > ans(3);
int maxsum = 0, maxcnt;
int n;



void rec(int ind, int sum, int cnt, int iter, int ressum){
    if (ressum != -1 && sum > ressum || cnt > maxcnt || sum > maxsum || !ans[0].empty())
        return;
    if (ind != -1) {
        used[ind] = 1;
        usedn[iter][ind] = 1;
        if (iter != 2 && cnt == maxcnt && (ressum == sum || ressum == -1))
            rec(-1, 0, 0, iter + 1, sum);
    }
    if (iter == 2 && cnt == maxcnt && sum == ressum){
        for (int i = 0; i < n; i++){
            for (int j = 0; j < 3; j++){
                if (usedn[j][i]) {
                    ans[j].push_back(i + 1);
                }
            }
        }
        return;
    }
    for (int i = ind + 1; i < n; i++){
        if (!used[i])
            rec(i, sum + gires[i], cnt + 1, iter, ressum);
    }

    if (ind == -1) return;

    used[ind] = 0;
    usedn[iter][ind] = 0;
}

void solve() {
    cin >> n;
    gires.resize(n);
    used.resize(n, 0);
    for (int j = 0; j < 3; j++) usedn[j].resize(n, 0);
    cin >> gires;
    for (auto i : gires) maxsum += i;
    maxsum /= 3;
    maxcnt = n / 3;
    if (n % 3 != 0){
        cout << "No solution";
        exit(0);
    }
    for (int i = 0; i < maxcnt; i++)
        rec(i, gires[i], 1, 0, -1);
    if (ans[0].empty()){
        cout << "No solution";
        exit(0);
    }
    cout << ans[0] << endl << ans[1] << endl << ans[2];
}


int32_t main() {
    setlocale(LC_ALL, "Russian");
#ifdef __APPLE__
    std::freopen("input.txt", "r", stdin);
    std::freopen("output.txt", "w", stdout);
#endif
    std::cin.tie(0);
    std::ios_base::sync_with_stdio(false);
//    int t;
//    cin >> t;
//    for (int i = 0; i < t; i++)
    solve();
    return 0;
}