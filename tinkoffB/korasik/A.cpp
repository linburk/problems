#include <iostream>
#include <queue>
#include <string>
#include <vector>

using std::cin, std::cout;
using std::vector, std::string, std::queue;

struct trie {
    struct node {
        int next[26] = { 0 };
        int link = 0;
        int tlink = 0;
        vector<int> term;
    };
    vector<node> tr;
    void add(string const& s, int i)
    {
        int n = 0;
        for (int pos = 0; pos < s.size(); ++pos) {
            int c = s[pos] - 'a';
            if (!tr[n].next[c]) {
                tr[n].next[c] = static_cast<int>(tr.size());
                tr.push_back(node());
            }
            n = tr[n].next[c];
        }
        tr[n].term.push_back(i);
    }
    void link()
    {
        queue<int> q;
        for (int i = 0; i < 26; ++i) {
            if (tr[0].next[i]) {
                q.push(tr[0].next[i]);
            }
        }
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int i = 0; i < 26; ++i) {
                if (tr[v].next[i]) {
                    int to = tr[v].next[i];
                    int link = tr[v].link;
                    while (link && tr[link].next[i] == 0)
                        link = tr[link].link;
                    tr[to].link = tr[link].next[i];
                    q.push(to);
                }
            }
        }
    }
    int up(int n)
    { // нахождение ближайшей терминальной вершины
        if (!n)
            return 0;
        if (!tr[n].tlink)
            tr[n].tlink = up(tr[n].link);
        return tr[n].term.size() ? n : tr[n].tlink;
    }
    trie()
    {
        tr.resize(1);
    }
};

int main()
{
#ifdef __APPLE__
    std::freopen(std::getenv("FINPATH"), "r", stdin);
    std::freopen(std::getenv("FOUTPATH"), "w", stdout);
#endif
    trie automaton;
    string t;
    cin >> t;
    int n;
    cin >> n;
    vector<int> size(n);
    vector<vector<int>> pos(n);
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        automaton.add(s, i);
        size[i] = static_cast<int>(s.size());
    }
    automaton.link();
    auto const& tr = automaton.tr;
    for (int cn = 0, i = 0; i < t.size(); ++i) {
        int c = t[i] - 'a';
        while (cn && !tr[cn].next[c])
            cn = tr[cn].link;
        cn = tr[cn].next[c];
        automaton.up(cn);
        int tn = cn;
        for (; tn; tn = tr[tn].tlink) {
            for (auto idx : tr[tn].term) {
                pos[idx].push_back(i - size[idx] + 1);
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << pos[i].size() << " \n"[pos[i].size() == 0];
        for (int j = 0; j < pos[i].size(); ++j) {
            cout << pos[i][j] + 1 << " \n"[j + 1 == pos[i].size()];
        }
    }
    return 0;
}
