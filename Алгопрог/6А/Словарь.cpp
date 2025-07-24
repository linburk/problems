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

    template <typename T>
    std::istream &operator>>(std::istream &is, std::pair<T, T> &p) {
        is >> p.first >> p.second;
        return is;
    }

}  // namespace tools
using namespace tools;

vector<bool> word_taken;
string text;
map<string, bool> dictionary;
vector<int> past;

void dp(int ind){
    string word;
    int j = ind;
    for (; j < text.size(); j++) {
        word += text[j];
        if (dictionary[word] && !word_taken[j + 1]){
            word_taken[j + 1] = 1;
            past[j + 1] = ind;
            dp(j + 1);
        }
    }
    if (word.size() == 0) {
        vector<string> ans;
        int res = past[ind];
        while (res != -1) {
            ans.push_back(text.substr(res, j - res));
            j = res;
            res = past[res];
        }
        for (int i = ans.size() - 1; i >= 0; i--) {
            cout << ans[i] << " ";
        }
        exit(0);
    }
}

void solve() {
    getline(cin, text);
    int n;
    cin >> n;
    cin.get();
    word_taken.resize(text.size() + 1, 0);
    past.resize(text.size() + 1, -1);
    for (int i = 0; i < n; i++){
        string s;
        getline(cin, s);
        dictionary[s] = 1;
    }
    dp(0); // ÑÑÐ¾ Ð´Ð¾Ð»Ð¶Ð½Ð¾ Ð±ÑÑÑ Ð¼Ð¾Ð¶Ð½Ð¾ ÑÐ°Ð·Ð²ÐµÑÐ½ÑÑÑ Ð² ÑÐ¸ÐºÐ»
}

int32_t main() {
    setlocale(LC_ALL, "Russian");
#ifndef __APPLE__
    std::cin.tie(0);
    std::cout.tie(0);
    std::ios_base::sync_with_stdio(false);
#endif
//    int t;
//    cin >> t;
//    for (int i = 0; i < t; i++)
    solve();
    return 0;
}