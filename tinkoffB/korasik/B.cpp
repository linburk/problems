#include <iostream>
#include <queue>
#include <string>
#include <vector>

using std::cin, std::cout;
using std::vector, std::string, std::queue;

struct trie {
    struct node {
        int next[26] = { 0 };
        vector<int> term;
    };
    vector<node> tr;
    void add(string const& s, int i)
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
        tr[n].term.push_back(i);
    }
    vector<int> sort()
    {
        vector<int> res;
        vector<int> q { 0 };
        while (!q.empty()) {
            int v = q.back();
            q.pop_back();
            res.insert(res.end(), tr[v].term.begin(), tr[v].term.end());
            for (int i = 26 - 1; i >= 0; --i) {
                if (tr[v].next[i]) {
                    q.push_back(tr[v].next[i]);
                }
            }
        }
        return res;
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
    trie tr;
    string t;
    cin >> t;
    int n = static_cast<int>(t.size());
    vector<string> word;
    vector<int> order;
    for (int i = 0; i < t.size();) {
        int j = i;
        if (t[i] != '.') {
            string s;
            for (; j < n && t[j] != '.'; ++j)
                s += t[j];
            tr.add(s, word.size());
            word.push_back(s);
            order.push_back(0);
        } else {
            for (; j < n && t[j] == '.'; ++j)
                ;
            order.push_back(j - i);
        }
        i = j;
    }
    vector<int> word_order = tr.sort();
    for (int i = 0, j = 0; i < order.size(); ++i) {
        if (order[i]) {
            for (int k = 0; k < order[i]; ++k)
                cout << '.';
        } else {
            cout << word[word_order[j++]];
        }
    }
}
