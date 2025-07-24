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


int n;
vector<int> ans(1300, -1);
vector<int> used(1300, 0);
vector<int> cubes(1300, 0);

void rec(int ind, int mod, int able){
    used[ind]++;
    if (mod == 0 && ans[0] == -1){
        ans = used;
        return;
    }
    if (able == 0 || ans[0] != -1 || ind == 0) {
        used[ind]--;
        return;
    }
    int tind = distance(cubes.begin(), upper_bound(all(cubes), mod)) - 1;
    for (int i = tind; i >= 1; i--){
        rec(i, mod - cubes[i], able - 1);
    }
    used[ind]--;
}

void solve() {
    for (int i = 0; i < 1300; i++)
        cubes[i] = i * i * i;
    cin >> n;
    rec(1300, n, 8);
    if (ans[0] == -1){
        cout << "IMPOSSIBLE";
        exit(0);
    }
    for (int i = 1; i < 1300; i++){
        while (ans[i] > 0) {
            ans[i]--;
            cout << i << " ";
        }
    }
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