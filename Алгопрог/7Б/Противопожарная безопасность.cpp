#include <bits/stdc++.h>
using namespace std;
 
typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<vi> vvi;
typedef vector<vl> vvl;
typedef vector<bool> vb;
typedef vector<vector<bool> > vvb;
 
#define all(cont) cont.begin(), cont.end()
#define funique(cont) cont.erase(unique(all(cont)), cont.end())

namespace tools {
mt19937_64 rng(chrono::steady_clock().now().time_since_epoch().count());
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
//        os << "\n";
        return os;
    }
    template <typename T, typename V>
    std::istream &operator>>(std::istream &is, std::pair<T, V> &p) {
        is >> p.first >> p.second;
        return is;
    }
}  // namespace tools
 
using namespace tools;

vvi gr, rev_gr;

class _condensate{
private:
    void topSort(vvi &gr, int v){
        if (used[v]) return;
        used[v] = 1;
        for (auto to : gr[v]) topSort(gr, to);
        order.push_back(v);
    }
    void getMember(vvi &rev_gr){
        used.assign(rev_gr.size(), 0);
        for (int v = order.size() - 1; v >= 0; v--){
            if (!used[order[v]]){
                getComponent(rev_gr, order[v], order[v]);
            }
        }
    }
    void getComponent(vvi &rev_gr, int v, int num){
        if (used[v]) return;
        used[v] = 1;
        member[v] = num;
        for (auto to : rev_gr[v]){
            getComponent(rev_gr, to, num);
        }
    }
protected:
    vvi cond_gr;
    vi member;
    vi order;
    vb used;
public:
    vi operator()(vvi &gr, vvi &rev_gr){
        used.resize(gr.size());
        member.resize(gr.size(), -1);
        for (int i = 0; i < gr.size(); i++){
            if (!used[i]){
                topSort(gr, i);
            }
        }
        getMember(rev_gr);
        return member;
    }
    
};

void solve() { // Ð¿Ð¾Ð¸ÑÐº Ð²ÑÐµÑ ÑÐ¸Ð»ÑÐ½Ð¾ÑÐ²ÑÐ·Ð½ÑÑ ÐºÐ¾Ð¼Ð¿Ð¾Ð½ÐµÐ½Ñ Ð¸ ÑÑÐ¾ÐºÐ¾Ð²
    int n, m;
    cin >> n >> m;
    gr.resize(n); rev_gr.resize(n);
    for (int a, b, i = 0; i < m; i++){
        cin >> a >> b;
        gr[a - 1].push_back(b - 1);
        rev_gr[b - 1].push_back(a - 1);
    }
    _condensate cond;
    vi mem = cond(gr, rev_gr);
    set<int> res;
    for (auto i : mem) res.insert(i);
    for (auto i : res) cout << i + 1 << "\n";
}

int32_t main() {
    setlocale(LC_ALL, "Russian");
#ifdef __APPLE__
    std::freopen("/Users/dmitrii/Documents/Code/Code/input.txt", "r", stdin);
    std::freopen("/Users/dmitrii/Documents/Code/Code/output.txt", "w", stdout);
#endif
    std::cin.tie(0);
    std::ios_base::sync_with_stdio(false);
//    int t; cin >> t; for (; t; t--)
    solve();
    return 0;
}