#include <iostream>
#include <numeric>
#include <queue>
#include <string>
#include <vector>
#include <list>

struct dsu {
    std::vector<int> rank, anc;
    dsu(int n)
    {
        rank.resize(n);
        anc.resize(n);
        std::iota(anc.begin(), anc.end(), 0);
    }
    int leader(int a) { return anc[a] == a ? a : anc[a] = leader(anc[a]); }
    void unite(int a, int b)
    {
        a = leader(a), b = leader(b);
        if (rank[a] > rank[b])
            std::swap(a, b);
        rank[b] = std::max(rank[a] + 1, rank[b]);
        anc[a] = b;
    }
};

struct trie {
    struct node {
        std::list<std::pair<char, int> > next;
        int link = 0;
        int tlink = 0;
        std::vector<int> term;
    };
    std::vector<node> tr;
    void add(std::string const& s, int i)
    {
        int n = 0;
        for (int pos = 0; pos < s.size(); ++pos) {
            int c = s[pos];
            int to = -1;
            for (auto&& [symb, to_] : tr[n].next) {
                if (symb == c) {
                    to = to_;
                    break;
                }
            }
            if (to == -1) {
                tr[n].next.push_back({c, static_cast<int>(tr.size())});
                to = tr[n].next.back().second;
                tr.push_back(node());
            }
            n = to;
        }
        tr[n].term.push_back(i);
    }
    void linking()
    {
        std::queue<int> q;
        for (auto&& [symb, to] : tr[0].next) {
            q.push(to);
        }
        for (; q.size();) {
            int v = q.front();
            q.pop();
            for (auto&& [symb, to] : tr[v].next) {
                int link = tr[v].link;
                int to2 = 0;
                bool f_ = 1;
                for (; f_ && !to2; link = tr[link].link) {
                    for (auto&& [symb2, to2_] : tr[link].next) {
                        if (symb2 == symb) {
                            to2 = to2_;
                            break;
                        }
                    }
                    if (link == 0)
                        f_ = 0;
                }
                tr[to].link = to2;
                q.push(to);
            }
        }
    }
    int up(int n)
    {
        if (!n)
            return 0;
        if (!tr[n].tlink)
            tr[n].tlink = up(tr[n].link);
        return tr[n].term.size() ? n : tr[n].tlink;
    }
    trie()
    {
        tr.resize(1);
        tr.reserve(1E6 + 1);
    }
};

std::vector<std::vector<std::pair<int, int>>> pos;

int t_size;

void prepare_0()
{
    std::string t;
    std::cin >> t;
    t_size = static_cast<int>(t.size());
    int n, k;
    std::cin >> n >> k;
    n += 26;
    std::vector<std::string> s(n);
    for (int i = 0; i < 26; ++i) {
        s[i] = 'a' + i;
    }
    for (int i = 26; i < n; ++i) {
        std::cin >> s[i];
    }
    trie tri;
    dsu ld(n);
    for (int i = 0; i < k; ++i) {
        int a, b;
        std::cin >> a >> b;
        ld.unite(a - 1, b - 1);
    }
    for (int i = 0; i < n; ++i) {
        tri.add(s[i], i);
    }
    tri.linking();
    pos.resize(t.size());
    auto const& tr = tri.tr;
    for (int cur_n = 0, i = 0; i < t.size(); ++i) {
        int c = t[i];
        bool f_ = 1;
        for (; f_; cur_n = tr[cur_n].link) {
            bool f = 0;
            for (auto&& [symb, to] : tr[cur_n].next) {
                if (symb == c) {
                    cur_n = to;
                    f = 1;
                    break;
                }
            }
            if (f)
                break;
            if (cur_n == 0)
                f_ = 0;
        }
        tri.up(cur_n);
        int t_n = cur_n;
        for (; t_n; t_n = tr[t_n].tlink) {
            for (auto j : tr[t_n].term) {
                pos[i - static_cast<int>(s[j].size()) + 1].push_back({ s[j].size(), ld.leader(j) + 1 });
            }
        }
    }
    for (int i = 0; i < t.size(); ++i) {
        std::sort(pos[i].begin(), pos[i].end());
    }
}

using i64 = long long;

static inline i64 mult(i64 a, i64 b, i64 mod)
{
    i64 res;
#if __arm64__
    res = (__int128)a * b % mod;
#elif __x86_64__
    __asm__(
        "imul %2\n"
        "idiv %3\n"
        : "=d"(res)
        : "a"(a), "d"(b), "r"(mod));
#endif
    return res;
}

i64 pow(i64 x, i64 p, i64 mod)
{
    i64 res = 1;
    for (; p; p >>= 1) {
        if (p & 1)
            res = mult(res, x, mod);
        x = mult(x, x, mod);
    }
    return res;
}

int const max_t_size = 500001;
i64 const mod = 1192533828546404621LL;
int const p = 56401;
int const bit_c = 20;
int up[max_t_size][bit_c];
i64 hash[max_t_size][bit_c];
i64 pow_2p[bit_c];
i64 pow_p[max_t_size];
void prepare_1()
{
    for (int i = 0; i < max_t_size; ++i) {
        for (int j = 0; j < bit_c; ++j) {
            up[i][j] = t_size;
        }
    }
    pow_p[0] = 1;
    for (int i = 0; i < t_size; ++i) {
        pow_p[i + 1] = mult(pow_p[i], p, mod);
    }
    for (int i = 0; i < bit_c; ++i) {
        pow_2p[i] = pow(p, 1 << i, mod);
    }
    for (int i = static_cast<int>(t_size) - 1; i >= 0; --i) {
        up[i][0] = pos[i].back().first + i;
        hash[i][0] = pos[i].back().second;
        for (int j = 1; j < bit_c; ++j) {
            up[i][j] = up[up[i][j - 1]][j - 1];
            hash[i][j] = (hash[i][j - 1] + mult(hash[up[i][j - 1]][j - 1], pow_2p[j - 1], mod)) % mod;
        }
    }
}

struct query {
    int len;
    int pos;
    i64 hash;
};

query get_up(int l, int r)
{
    int end_p = l;
    int len = 0;
    i64 hash_r = 0;
    for (int i = bit_c - 1; i >= 0; --i) {
        if (up[end_p][i] < r) {
            hash_r = (hash_r + mult(hash[end_p][i], pow_p[len], mod)) % mod;
            len += (1 << i);
            end_p = up[end_p][i];
        }
    }
    return { len, end_p, hash_r };
}

int main(int argc, char* argv[])
{
#ifndef __APPLE__
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
#endif
    prepare_0();
    prepare_1();
    int q;
    std::cin >> q;
    for (int i = 0; i < q; ++i) {
        int a, b, c, d;
        std::cin >> a >> b >> c >> d;
        int l = --a, r = --c;
        bool tr = 1;
        auto f = get_up(l, b);
        auto s = get_up(r, d);
        l = f.pos;
        r = s.pos;
        int cl, cr;
        for (; l < b;) {
            auto p = *--std::upper_bound(pos[l].begin(), pos[l].end(), std::pair<int, int> { b - l, 1E9 });
            cl = p.second;
            f.hash = (f.hash + mult(cl, pow_p[f.len], mod)) % mod;
            ++f.len;
            l += p.first;
        }
        for (; r < d; ) {
            auto p = *--std::upper_bound(pos[r].begin(), pos[r].end(), std::pair<int, int> { d - r, 1E9 });
            cr = p.second;
            s.hash = (s.hash + mult(cr, pow_p[s.len], mod)) % mod;
            ++s.len;
            r += p.first;
        }
        if (f.hash != s.hash)
            tr = 0;
        std::cout << (tr ? "Yes\n" : "No\n");
    }
    return 0;
}
