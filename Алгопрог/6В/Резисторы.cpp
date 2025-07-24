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
ld cres;
ld cmindif = -1e9;
vector<ld> conds;

void rec(){
    for (int i = 0; i < n; i++){
        for (int j = i + 1; j < n; j++){
            ld c1 = conds[i], c2 = conds[j];
            conds[j] = conds[n - 1];
            n--;
            conds[i] = c1 + c2;
            if (abs(conds[i] - cres) < abs(cmindif - cres))
                cmindif = conds[i];
            rec();
            conds[i] = (c1 * c2) / (c1 + c2);
            if (abs(conds[i] - cres) < abs(cmindif - cres))
                cmindif = conds[i];
            rec();
            n++;
            conds[n - 1] = conds[j], conds[i] = c1, conds[j] = c2;
        }
    }
}

void solve() {
    cin >> n >> cres;
    conds.resize(n);
    cin >> conds;
    for (auto c : conds){
        if (abs(cres - c) < abs(cres - cmindif)){
            cmindif = c;
        }
    }
    rec();
    cout << setprecision(7) << fixed << cmindif;
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