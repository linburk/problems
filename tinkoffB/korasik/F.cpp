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
        array<int, 2> next;
        array<int, 2> go;
        int link = 0;
        char sterm = -1;
        bool term = 0;
    };
    vector<node> tr;
    void add(string const& s)
    {
        int n = 0;
        for (auto c : s) {
            c -= '0';
            if (!tr[n].next[c]) {
                tr[n].next[c] = static_cast<int>(tr.size());
                tr.push_back(node());
            }
            n = tr[n].next[c];
        }
        tr[n].term = true;
    }
    void link()
    {
        tr[0].sterm = 0;
        queue<int> q;
        for (int i = 0; i < 2; ++i) {
            tr[0].go[i] = tr[0].next[i];
            if (tr[0].next[i]) {
                q.push(tr[0].next[i]);
            }
        }
        while (!q.empty()) {
            int n = q.front();
            q.pop();
            for (int i = 0; i < 2; ++i) {
                int link = tr[tr[n].link].go[i];
                int to = tr[n].next[i];
                if (to) {
                    tr[n].go[i] = to;
                    tr[to].link = link;
                    q.push(to);
                } else {
                    tr[n].go[i] = link;
                }
            }
        }
        for (int i = 0; i < tr.size(); ++i)
            up(i);
    }
    trie()
    {
        tr.resize(1);
    }
    bool up(int n)
    {
        if (tr[n].sterm == -1)
            tr[n].sterm = tr[n].term || up(tr[n].link);
        return tr[n].sterm;
    }
    int size() { return static_cast<int>(tr.size()); }
} automaton;

auto const& gr = automaton.tr;
vector<int> cnd;
bool res = false;

void dfs(int v)
{
    cnd[v] = 1;
    for (int i = 0; i < 2; ++i) {
        int to = gr[v].go[i];
        if (gr[to].sterm)
            continue;
        if (cnd[to] == 0)
            dfs(to);
        if (cnd[to] == 1)
            res = true;
    }
    cnd[v] = 2;
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
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        automaton.add(s);
    }
    automaton.link();
    cnd.resize(automaton.size());
    dfs(0);
    cout << (res ? "TAK" : "NIE") << "\n";
}
