#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using std::cin, std::cout, std::string;
using std::vector, std::queue, std::array, std::pair;
using i64 = long long;

int n, m, k;
i64 const inf = 1E18;

struct trie {
    struct node {
        array<int, 10> next;
        int link = 0;
        int count = 0;
    };
    vector<node> tr;
    void add(string const& s)
    {
        int n = 0;
        ++tr[0].count;
        for (auto c : s) {
            c -= '0';
            if (!tr[n].next[c]) {
                tr[n].next[c] = static_cast<int>(tr.size());
                tr.push_back(node());
            }
            n = tr[n].next[c];
            ++tr[n].count;
        }
    }
    trie()
    {
        tr.resize(1);
    }
} bor;

int main()
{
    cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
#ifdef __APPLE__
    std::freopen(std::getenv("FINPATH"), "r", stdin);
    std::freopen(std::getenv("FOUTPATH"), "w", stdout);
#endif
    cin >> n >> m >> k;
    vector<i64> a(m);
    for (auto&& i : a)
        cin >> i;
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        bor.add(s);
    }
    auto const& gr = bor.tr;
    vector<vector<i64>> dp(m + 1, vector<i64>(gr.size() + 1, inf));
    vector<vector<pair<char, int>>> pr(m + 1, vector<pair<char, int>>(gr.size() + 1));
    dp[0][0] = 0;
    for (int i = 0; i < m; ++i) {
        for (int v = 0; v < gr.size(); ++v) {
            if (dp[i][v] == inf)
                continue;
            for (int j = 0; j < k; ++j) {
                int to = gr[v].next[j];
                if (!to && dp[i][v] < dp[i + 1][gr.size()]) {
                    dp[i + 1][gr.size()] = dp[i][v];
                    pr[i + 1][gr.size()] = { '0' + j, v };
                } else {
                    i64 add = 1ll * gr[to].count * a[i];
                    if (i)
                        add -= 1ll * gr[to].count * a[i - 1];
                    if (dp[i + 1][to] > dp[i][v] + add) {
                        dp[i + 1][to] = dp[i][v] + add;
                        pr[i + 1][to] = { '0' + j, v };
                    }
                }
            }
        }
    }
    i64 res = inf;
    int ir, vr;
    for (int i = 0; i < m; ++i) {
        if (dp[i][gr.size()] < res) {
            res = dp[i][gr.size()];
            ir = i;
            vr = gr.size();
        }
    }
    for (int v = 0; v <= gr.size(); ++v) {
        if (dp[m][v] < res) {
            res = dp[m][v];
            ir = m;
            vr = v;
        }
    }
    string ans;
    if (ir != m) {
        for (int j = ir; j < m; ++j) {
            ans += '0';
        }
    }
    while (ir) {
        auto [pc, pv] = pr[ir][vr];
        ans += pc;
        vr = pv;
        --ir;
    }
    std::reverse(ans.begin(), ans.end());
    cout << ans << '\n'
         << res << '\n';
}
