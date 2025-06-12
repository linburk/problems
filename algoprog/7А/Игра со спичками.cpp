#include <bits/stdc++.h>
using namespace std;
 
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
 
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


const int SIZE = 10001;
static inline vector<bool>  buildPrimes(){
    vector<bool> Primes(SIZE, 1);
    Primes[1] = 0;
    Primes[0] = 0;
    for (int i = 2; i <= sqrt(SIZE); i++){
        if (Primes[i]){
            for (int j = i + i; j < SIZE; j += i){
                Primes[j] = 0;
            }
        }
    }
    return Primes;
}
static vector<bool> isPrime = buildPrimes();


static vector<bool> win(SIZE, 0), lose(SIZE, 0), used(SIZE, 0);
static vector<int> degree(SIZE, 0);


static inline vector<vector<int> >  buildGraph(){
    vector<vector<int> > _graph(SIZE);
    for (int i = 0; i < SIZE; i++){
        if (isPrime[i]) continue;
        if (i < SIZE - 1){
            _graph[i].push_back(i + 1);
            degree[i + 1]++;
        }
        if (i < SIZE - 2){
            _graph[i].push_back(i + 2);
            degree[i + 2]++;
        }
        if (i < SIZE - 3){
            _graph[i].push_back(i + 3);
            degree[i + 3]++;
        }
    }
    return _graph;
}

static vector<vector<int> > graph = buildGraph();

void dfs(int v){
    if (used[v]) return;
    used[v] = 1;
    for (int to : graph[v]){
        if (!used[to]){
            if (lose[v]) win[to] = 1;
            else if (--degree[to] == 0) lose[to] = 1;
            else continue;
            dfs(to);
        }
    }
}

void solve(){
    win[0] = 1;
    lose[4] = 1;
    dfs(0);
    win[1] = 1;
    win[2] = 1;
    win[3] = 1;
    int n;
    cin >> n;
    cout << (win[n] & !lose[n] ? 1 : 2);
}

 
int32_t main() {
    setlocale(LC_ALL, "Russian");
#ifdef __APPLE__
    std::freopen("/Users/dmitrii/Documents/Code/Code/input.txt", "r", stdin);
    std::freopen("/Users/dmitrii/Documents/Code/Code/output.txt", "w", stdout);
#endif
//    std::cin.tie(0);
//    std::ios_base::sync_with_stdio(false);
//    int t;
//    cin >> t;
//    for (int i = 0; i < t; i++)
    solve();
    return 0;
}