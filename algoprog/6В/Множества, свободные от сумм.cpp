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

ll cnt = 0;
vector<bool> used(35, 0), usable(35, 1);
void rec(int ind, int n){
    if (ind < n) {
        used[ind] = 0;
        rec(ind + 1, n);
        if (usable[ind] && !used[(ind + ind) % n]) {
            used[ind] = 1;
            vector<bool> usable_c = usable;
            for (int j = 1; j <= ind; j++)
                if (used[j]) {
                    usable[(j + ind) % n] = 0;
                }
            rec(ind + 1, n);
            usable = usable_c;
            used[ind] = 0;
        }
    } else {
//        for (int i = 0; i < n; i++){
//            if (used[i]) cout << i << " ";
//        }
//        cout << endl;
        cnt++;
    }
}

void solve() {
    int n;
    cin >> n;
    vector<int> numbs(n);
    iota(all(numbs), 0);
    for (int i = 0; i < n; i++)
        if ((i + i) % n == i) usable[i] = 0;
    rec(1, n);
    cout << cnt;
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