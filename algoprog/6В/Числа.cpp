#include <bits/stdc++.h>
using namespace std;

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

#define endl '\n'
#define all(cont) cont.begin(), cont.end()
#define funique(cont) cont.erase(unique(all(cont)), cont.end())

namespace tools {
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
vector<int> ans, res;
ll c = 0, m = 1e9;
list<int> a;

void rec(){
    if (c < m && a.size() == 2){
        m = c;
        res = ans;
    }
    if (c > m || a.size() == 2) return;
    list<int>::iterator t = a.begin(); t++;
    for (int j = 1; j < a.size() - 1; j++){
        ans.push_back(j);
        auto next = t, prev = t; next++; prev--;
        c += *t * (*next + *prev);
        int te = *t;
        a.erase(t);
        rec();
        a.insert(next, te);
        c -= *t * (*next + *prev);
        ans.pop_back();
        t++;
    }
}


void solve(){
    int n;
    cin >> n;
    a.resize(n);
    for (auto &i : a) cin >> i;
    rec();
    cout << m;
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
//    for (int i = 0; i < t; i++)
    solve();
    return 0;
}