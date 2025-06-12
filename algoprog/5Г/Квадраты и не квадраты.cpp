#include <stdio.h>

#include <algorithm>
#include <bitset>
#include <cmath>
#include <deque>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>

#ifdef __APPLE__
#include <fstream>
std::ifstream input("input.txt");
std::ofstream output("output.txt");
#define cin input
#define cout output
#endif

using namespace std;

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

#define endl '\n'
#define all(cont) cont.begin(), cont.end()
#define pb(x) emplace_back(x)
#define $FASTSTREAM \
  std::cin.tie(0);  \
  std::cout.tie(0); \
  std::ios_base::sync_with_stdio(false);

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

    template <typename T>
    std::istream &operator>>(std::istream &is, std::pair<T, T> &p) {
        is >> p.first >> p.second;
        return is;
    }

}  // namespace tools
using namespace tools;
vector<bool> squares(1e9 + 1, 0);
int make_sqr(int a){
//    cout << pow(ceil(sqrt(a)), 2) << " " << pow(ceil(sqrt(a) - 1), 2) << " " << a << endl;
    return min(abs(a - pow(ceil(sqrt(a)), 2)), abs(a - pow(ceil(sqrt(a) - 1), 2)));
}
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < sqrt(1e9); i++){
        squares[i * i] = 1;
    }
    cin >> a;
    int cnt2 = 0, cntn2 = 0;
    vector<int> sqrts, nsqrts;
    for (int i = 0; i < n; i++){
        if (squares[a[i]]) {
            cnt2++;
            sqrts.push_back(a[i]);
        }
        else {
            cntn2++;
            nsqrts.push_back(a[i]);
        }
    }
    int ans = 0;
    if (cnt2 > cntn2){
        sort(all(sqrts), greater<int>());
        auto it = sqrts.begin();
        while (cnt2 != cntn2){
            if (*it == 0){
                ans += 2;
            }
            else {
                ans++;
            }
            cntn2++;
            cnt2--;
            it++;
        }
    }
    if (cnt2 < cntn2){
        vector<int> cnt_to_2(nsqrts.size());
        for (int i = 0; i < nsqrts.size(); i++){
            cnt_to_2[i] = make_sqr(nsqrts[i]);
        }
        sort(all(cnt_to_2));
        auto it = cnt_to_2.begin();
        while (cnt2 < cntn2){
            ans += *it;
            it++;
            cntn2--;
            cnt2++;
        }
    }
    cout << ans;
}

int32_t main() {
    setlocale(LC_ALL, "Russian");
#ifndef __APPLE__
    $FASTSTREAM
#endif
//    int t;
//    cin >> t;
//    for (int i = 0; i < t; i++)
    solve();
    return 0;
}