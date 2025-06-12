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

vector<int> number(16);
vector<vector<int> > ans(4, vector<int>(4, -1));
vector<vector<int> > temp(4, vector<int>(4, -1));
vector<bool> used(16, 0);
vector<vector<int> > pref_hor(4, vector<int>(4, 0));
vector<vector<int> > pref_vert(4, vector<int>(4, 0));
int sum = 0;
void rec(int ind, int i, int j) {
    if (ans[0][0] != -1) return;
    used[ind] = 1;
    temp[i][j] = number[ind];
    pref_hor[i][j] = (j == 0 ? number[ind] : pref_hor[i][j - 1] + number[ind]);
    pref_vert[i][j] = (i == 0 ? number[ind] : pref_vert[i - 1][j] + number[ind]);
    if ((j == 3 || i > 0) && pref_hor[0][3] * 4 != sum){
        used[ind] = 0;
        return;
    }
    if (i != 0 && pref_hor[i][j] > pref_hor[0][3] || j == 3 && pref_hor[i][j] != pref_hor[0][3]) {
        used[ind] = 0;
        return;
    }
    if (i != 0 && pref_vert[i][j] > pref_hor[0][3] || i == 3 && pref_vert[i][j] != pref_hor[0][3]) {
        used[ind] = 0;
        return;
    }
    if (i == 3 && j == 3 && ans[0][0] == -1) {
        ans = temp;
        return;
    }
    for (int m = 0; m < 16; m++)
        if (!used[m]) {
            if (j == 3) {
                rec(m, i + 1, 0);
            } else {
                rec(m, i, j + 1);
            }
        }
    used[ind] = 0;
    return;
}


void solve() {
    cin >> number;
    for (auto i : number)
        sum += i;
    for (int i = 0; i < 16; i++){
        if (ans[0][0] == -1) rec(i, 0, 0);
    }
    if (ans[0][0] == -1){
        cout << "NO SOLUTION";
        exit(0);
    }
    cout << ans;

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