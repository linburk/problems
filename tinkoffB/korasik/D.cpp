#include <cassert>
#include <chrono>
#include <iostream>
#include <list>
#include <queue>
#include <string>
#include <vector>

using std::cin, std::cout;
using std::pair, std::vector, std::string, std::queue, std::list;

struct trie {
    struct node {
        int next[26] = { 0 };
        int go[26] = { 0 };
        int link = 0;
        long long val = -1;
        int term = 0;
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
                    tr[v].go[i] = tr[v].next[i];
                    int to = tr[v].next[i];
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
    long long up(int n)
    {
        if (tr[n].val == -1)
            tr[n].val = tr[n].term + up(tr[n].link);
        return tr[n].val;
    }
    trie()
    {
        tr.resize(1);
    }
};

vector<vector<pair<char, int>>> tr;
vector<bool> used;
trie automaton;
auto const& tra = automaton.tr;

long long res = 0;
void bfs()
{
    queue<pair<int, int>, list<pair<int, int>>> q;
    q.push({ 0, 0 });
    while (!q.empty()) {
        auto [v, n] = q.front();
        q.pop();
        res += tra[n].val;
        for (auto [c, to] : tr[v]) {
            int cn = tra[n].go[c];
            q.push({ to, cn });
        }
    }
}

int main()
{
    cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
#ifdef __APPLE__
    std::freopen(std::getenv("FINPATH"), "r", stdin);
    std::freopen(std::getenv("FOUTPATH"), "w", stdout);
#endif
    int n;
    cin >> n;
    used.resize(n);
    tr.resize(n);
    for (int i = 0; i < n; ++i) {
        int k;
        cin >> k;
        for (int j = 0; j < k; ++j) {
            int to;
            char c;
            cin >> to >> c;
            tr[i].push_back({ c - 'a', to - 1 });
        }
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        string s;
        cin >> s;
        automaton.add(s);
    }
    automaton.link();
    bfs();
    cout << res << "\n";
}
