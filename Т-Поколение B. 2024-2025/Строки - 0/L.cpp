#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <functional>

int main()
{   using i64 = long long;
    int mod = 1E9+7;
    int p = 1E5+3;
    std::vector<i64> pow(200001);
    pow[0] = 1;
    for (int i = 0; i < 200000; ++i) {
        pow[i + 1] = pow[i] * p % mod;
    }
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;
for (; t--; )
{  
    int n;
    std::cin >> n;
    std::vector<std::vector<int> > gr(n);
    std::vector<i64> hash(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;
        gr[u].push_back(v);
        gr[v].push_back(u);
    }
    std::function<void(int, int)> to_hash = [&] (int v, int pr) {
        hash[v] = 52;
        std::vector<i64> ch;
        for (auto to : gr[v]) {
            if (to != pr) {
                to_hash(to, v);
                ch.push_back(hash[to]); 
            }
        }
        std::sort(ch.begin(), ch.end());
        for (int i = 0; i < ch.size(); ++i) {
            hash[v] = (hash[v] + ch[i] * ch[i] % mod + ch[i] * pow[i] % mod) % mod;
        }
    };
    std::function<bool(int, int)> is_symm = [&] (int v, int pr) {
        std::map<i64, int> ch_h;
        for (auto to : gr[v]) {
            if (to != pr) {
                if (ch_h[hash[to]]) {
                    ch_h[hash[to]] = 0;
                } else {
                    ch_h[hash[to]] = to;
                }
            }
        }
        int mid = 0;
        for (auto [f, s] : ch_h) {
            if (s) {
                if (mid)
                    return false;
                else
                    mid = s;
            }
        }
        ch_h.clear();
        if (mid)
            return is_symm(mid, v);
        return true;
    };
    to_hash(0, 0);
    std::cout << (is_symm(0, 0) ? "YES\n" : "NO\n");
}
}
