#include <algorithm>
#include <array>
#include <cassert>
#include <chrono>
#include <iostream>
#include <list>
#include <numeric>
#include <queue>
#include <string>
#include <vector>

using std::cin, std::cout;
using std::pair, std::vector, std::string, std::queue, std::list, std::array;

struct trie {
    struct node {
        int next[26] = { 0 };
        int go[26] = { 0 };
        int link = 0;
        int term = 0;
        int val = -1;
    };
    vector<node> tr;
    void add(string const& s)
    {
        int n = 0;
        for (auto c : s) {
            c -= 'a';
            if (!tr[n].next[c]) {
                tr[n].next[c] = static_cast<int>(tr.size());
                tr.push_back(node());
            }
            n = tr[n].next[c];
        }
        ++tr[n].term;
    }
    void link()
    {
        tr[0].val = 0;
        queue<int> q;
        for (int i = 0; i < 26; ++i) {
            tr[0].go[i] = tr[0].next[i];
            if (tr[0].next[i]) {
                q.push(tr[0].next[i]);
            }
        }
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int i = 0; i < 26; ++i) {
                int link = tr[tr[v].link].go[i];
                if (tr[v].next[i]) {
                    int to = tr[v].next[i];
                    tr[v].go[i] = to;
                    tr[to].link = link;
                    q.push(to);
                } else {
                    tr[v].go[i] = link;
                }
            }
        }
        for (int i = 0; i < tr.size(); ++i)
            up(i);
    }
    int up(int n)
    {
        if (tr[n].val == -1)
            return tr[n].val = tr[n].term + up(tr[n].link);
        return tr[n].val;
    }
    trie()
    {
        tr.resize(1);
    }
};
int main()
{
    cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
#ifdef __APPLE__
    std::freopen(std::getenv("FINPATH"), "r", stdin);
    std::freopen(std::getenv("FOUTPATH"), "w", stdout);
#endif
    int const mod = 10000;
    trie automaton;
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < k; ++i) {
        string s;
        cin >> s;
        automaton.add(s);
    }
    automaton.link();
    auto const& tra = automaton.tr;
    vector<vector<array<int, 2>>> dp(n + 1, vector<array<int, 2>>(tra.size()));
    dp[0][0][0] = 1;
    for (int c = 0; c < n; ++c) {
        for (int i = 0; i < tra.size(); ++i) {
            for (int j = 0; j < 26; ++j) {
                int to = tra[i].go[j];
                for (int k = 0; k < 2; ++k) {
                    dp[c + 1][to][k || tra[to].val] = (dp[c + 1][to][k || tra[to].val] + dp[c][i][k]) % mod;
                }
            }
        }
    }
    long long res = 0;
    for (int i = 0; i < tra.size(); ++i)
        res = (res + dp[n][i][1]) % mod;
    cout << res << "\n";
}
