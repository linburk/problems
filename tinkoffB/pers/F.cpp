#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <climits>
#include <deque>
#include <functional>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using i64 = long long;

using std::cin, std::cout;
using std::vector, std::array, std::deque, std::pair, std::string;

struct tree {
    struct node {
        bool set = 0;
        int val = INT_MIN;
        int l = 0;
        int r = 0;
    };
    vector<node> data;
    void overwrite(int n)
    {
        int ln = data[n].l;
        int rn = data[n].r;
        data[n].val = std::max(data[ln].val, data[rn].val);
    }
    void push(int n, int l, int r)
    {
        int ln = data[n].l;
        int rn = data[n].r;
        if (data[n].set) {
            data[n].val = r - 1;
            if (r - l > 1) {
                int m = (l + r) >> 1;
                data[ln].set = 1;
                data[ln].val = m - 1;
                data[rn].set = 1;
                data[rn].val = r - 1;
            }
            data[n].set = 0;
        }
    }
    void copy(int n)
    {
        data.push_back(data[data[n].l]);
        data[n].l = data.size() - 1;
        data.push_back(data[data[n].r]);
        data[n].r = data.size() - 1;
    }
    int max(int ql, int qr, int l, int r, int n)
    {
        if (l >= qr || r <= ql || !n)
            return INT_MIN;
        copy(n);
        push(n, l, r);
        if (ql <= l && r <= qr)
            return data[n].val;
        int m = (l + r) >> 1;
        int res = std::max(max(ql, qr, l, m, data[n].l),
            max(ql, qr, m, r, data[n].r));
        data.pop_back();
        data.pop_back();
        return res;
    }
    void set(int ql, int qr, int l, int r, int n)
    {
        if (l >= qr || r <= ql)
            return;
        copy(n);
        push(n, l, r);
        if (ql <= l && r <= qr) {
            data[n].set = 1;
            push(n, l, r);
            return;
        }
        int m = (l + r) >> 1;
        set(ql, qr, l, m, data[n].l);
        set(ql, qr, m, r, data[n].r);
        overwrite(n);
    }
    void set(int i, int l, int r, int n)
    {
        copy(n);
        push(n, l, r);
        if (l == r - 1) {
            data[n].val = INT_MIN;
            return;
        }
        int m = (l + r) >> 1;
        if (i < m)
            set(i, l, m, data[n].l);
        else
            set(i, m, r, data[n].r);
        overwrite(n);
    }
    int size;

public:
    tree(int n)
    {
        size = n;
        data.resize(2);
        data.reserve(323E5);
    }
    int set(int i, int n)
    {
        data.push_back(data[n]);
        n = data.size() - 1;
        set(i, 0, size, n);
        return n;
    }
    int set(int ql, int qr, int n)
    {
        data.push_back(data[n]);
        n = data.size() - 1;
        set(ql, qr, 0, size, n);
        return n;
    }
    int max(int ql, int qr, int n)
    {
        data.push_back(data[n]);
        n = data.size() - 1;
        int res = max(ql, qr, 0, size, n);
        data.pop_back();
        return res;
    }
};

struct entity {
    int hp;
    int dmg;
    int p2;
};

struct query {
    int type;
    int a, b;
};

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
    vector<entity> npc;
    vector<int> t;
    vector<query> q(n);
    vector<int> max_hp(n, 1);
    for (int i = 0; i < n; ++i) {
        cin >> q[i].type;
        if (q[i].type == 5) {
            cin >> q[i].a >> q[i].b;
            --q[i].a, --q[i].b;
        } else if (q[i].type != 1) {
            cin >> q[i].a;
            --q[i].a;
        }
        if (q[i].type == 3)
            ++max_hp[q[i].a];
    }
    int sz = *std::max_element(max_hp.begin(), max_hp.end());
    max_hp.clear();
    tree tr(sz);
    auto attack = [&](int& hp, int dmg, int p2) {
        dmg = p2 - dmg - 1;
        int pos = tr.max(0, dmg + 1, hp);
        if (pos == INT_MIN) {
            hp = 0;
            return;
        }
        hp = tr.set(pos, hp);
        if (pos != dmg)
            hp = tr.set(pos + 1, dmg + 1, hp);
        if (tr.data[hp].val == INT_MIN)
            hp = 0;
    };
    int root = tr.set(0, 1, 1);
    for (int i = 0; i < n; ++i) {
        auto [type, a, b] = q[i];
        switch (type) {
        case 1:
            npc.push_back({ root, 0, 1 });
            t.push_back(-1);
            break;
        default:
            switch (type) {
            case 2:
                ++npc[a].dmg;
                break;
            case 3:
                ++npc[a].p2;
                break;
            case 4:
                npc.push_back(npc[a]);
                if (npc.back().hp == 0) {
                    t.push_back(i + 1);
                } else {
                    t.push_back(-1);
                }
                break;
            case 5:
                if (t[a] > 0 || t[b] > 0)
                    continue;
                attack(npc[a].hp, npc[b].dmg, npc[a].p2);
                attack(npc[b].hp, npc[a].dmg, npc[b].p2);
                if (npc[a].hp == 0) {
                    t[a] = i + 1;
                }
                if (npc[b].hp == 0) {
                    t[b] = i + 1;
                }
                break;
            }
        }
    }
    cout << t.size() << "\n";
    for (int i = 0; i < t.size(); ++i) {
        cout << t[i] << " ";
    }
}
