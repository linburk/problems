#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>

using std::cin, std::cout;
using std::vector, std::string, std::queue, std::map;

int k;
struct trie {
    struct node {
        int next[2] = { 0 };
        int c = 0;
    };
    vector<node> tr;
    void oper(int x, int add = 1)
    {
        int n = 0;
        tr[n].c += add;
        for (int i = k - 1; i >= 0; --i) {
            int bit = x >> i & 1;
            if (!tr[n].next[bit]) {
                tr[n].next[bit] = static_cast<int>(tr.size());
                tr.push_back(node());
            }
            n = tr[n].next[bit];
            tr[n].c += add;
        }
    }
    int find(int x)
    {
        int res = 0;
        int n = 0;
        for (int i = k - 1; i >= 0; --i) {
            int bit = x >> i & 1;
            if (!tr[n].next[bit] || tr[tr[n].next[bit]].c == 0) {
                n = tr[n].next[!bit];
                res |= (!bit) << i;
            } else {
                n = tr[n].next[bit];
                res |= bit << i;
            }
        }
        return res;
    }
    trie()
    {
        tr.resize(1);
    }
};

void solve()
{
    int n;
    cin >> n >> k;
    vector<int> a(n);
    map<int, int> pos;
    trie tr;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        pos[a[i]] = i;
        tr.oper(a[i]);
    }
    int res = -1;
    int ir = 0, jr = 0, xr = 0;
    for (int i = 0; i < n; ++i) {
        tr.oper(a[i], -1);
        int f = tr.find(a[i]);
        tr.oper(a[i]);
        int cur = 0;
        int cx = 0;
        for (int j = 0; j < k; ++j) {
            if ((a[i] >> j & 1) == (f >> j & 1)) {
                cur |= 1 << j;
                if (!(a[i] >> j & 1))
                    cx |= 1 << j;
            }
        }
        if (cur > res) {
            res = cur;
            ir = i;
            jr = pos[f];
            xr = cx;
        }
    }
    cout << ir + 1 << " " << jr + 1 << " " << xr << "\n";
}

int main()
{
    cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
#ifdef __APPLE__
    std::freopen(std::getenv("FINPATH"), "r", stdin);
    std::freopen(std::getenv("FOUTPATH"), "w", stdout);
#endif
    int t;
    cin >> t;
    while (t--)
        solve();
}
