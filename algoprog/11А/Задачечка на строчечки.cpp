#include <iostream>
#include <numeric>
#include <queue>
#include <string>
#include <vector>

struct trie {
    struct node {
        int next[26] = {};
        int link = 0;
        int tlink = 0;
        std::vector<int> term;
    };
    std::vector<node> tr;
    void add(std::string const& s, int i, int n = 0, int pos = 0)
    {
        if (pos == s.size()) {
            tr[n].term.push_back(i);
            return;
        }
        int c = s[pos] - 'a';
        if (!tr[n].next[c]) {
            tr[n].next[c] = static_cast<int>(tr.size());
            tr.push_back(node());
        }
        add(s, i, tr[n].next[c], pos + 1);
    }
    void linking()
    {
        std::queue<int> q;
        for (int i = 0; i < 26; ++i) {
            if (tr[0].next[i]) {
                q.push(tr[0].next[i]);
            }
        }
        for (; q.size();) {
            int v = q.front();
            q.pop();
            for (int i = 0; i < 26; ++i) {
                if (tr[v].next[i]) {
                    int to = tr[v].next[i];
                    int link = tr[v].link;
                    for (; link && tr[link].next[i] == 0; link = tr[link].link)
                        ;
                    tr[to].link = tr[link].next[i];
                    q.push(to);
                }
            }
        }
    }
    int up(int n)
    {
        if (!n) return 0;
        if (tr[n].tlink)
            return tr[n].tlink;
        tr[n].tlink = up(tr[n].link);
        return tr[n].term.size() ? n : tr[n].tlink;
    }
    trie()
    {
        tr.resize(1);
    }
};

int main(int argc, char* argv[])
{
    std::string t;
    std::cin >> t;
    int n;
    std::cin >> n;
    std::vector<std::string> s(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> s[i];
    }
    trie tri;
    std::vector<std::vector<int>> pos(n);
    for (int i = 0; i < n; ++i) {
        tri.add(s[i], i);
    }
    tri.linking();
    auto const& tr = tri.tr;
    for (int cur_n = 0, i = 0; i < t.size(); ++i) {
        int c = t[i] - 'a';
        if (tr[cur_n].next[c]) {
            cur_n = tr[cur_n].next[c];
        } else {
            for (; cur_n && !tr[cur_n].next[c]; cur_n = tr[cur_n].link);
            cur_n = tr[cur_n].next[c];
        }
        tri.up(cur_n);
        int t_n = cur_n;
        for (; t_n; t_n = tr[t_n].tlink) {
            for (auto j : tr[t_n].term) {
                pos[j].push_back(i - s[j].size() + 1);
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        std::cout << pos[i].size() << " \n"[pos[i].size() == 0];
        for (int j = 0; j < pos[i].size(); ++j) {
            std::cout << pos[i][j] + 1 << " \n"[j == pos[i].size() - 1];
        }
    }
    return 0;
}