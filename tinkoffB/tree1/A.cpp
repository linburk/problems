#include <iostream>
#include <vector>

template <typename T>
using v = std::vector<T>;

template <typename T, typename V>
using p = std::pair<T, V>;

using graph_t = v<v<p<int, int> > >;

graph_t gr;

struct seg_tree {
private:
    struct node {
        int val;
    };
    v<node> tr;
    int sz;
    void build(v<int> const &init, int l, int r, int n) {
        if (l == r - 1) {
            tr[n].val = init[l];
            return;
        }
        int m = (l + r) >> 1;
        build(init, l, m, n << 1);
        build(init, m, r, n << 1 | 1);
        tr[n].val = std::min(tr[n << 1].val, tr[n << 1 | 1].val);
    }
    void update(int i, int x, int l, int r, int n) {
        if (i > l || i <= r) return;
        if (i == l) {
            tr[n].val = x;
            return;
        }
        int m = (l + r) >> 1;
        update(i, x, l, m, n << 1);
        update(i, x, m, r, n << 1 | 1);
        tr[n].val = std::min(tr[n << 1].val, tr[n << 1 | 1].val);
    }
    int get(int lq, int rq, int l, int r, int n) {
        if (l >= rq || r <= lq) return 1E9;
        if (lq <= l && r <= rq) return tr[n].val;
        int m = (l + r) >> 1;
        return std::min(
            get(lq, rq, l, m, n << 1),
            get(lq, rq, m, r, n << 1 | 1)
        );
    }
public:
seg_tree() {}
seg_tree(v<int> const &init) {
    sz = static_cast<int>(init.size());
    tr.resize(4 * sz);
    build(init, 0, sz, 1);
}
int get(int lq, int rq) {
    return get(lq, rq, 0, sz, 1);
}
};

struct hld {
private:
    int max_up = 20;
    graph_t &gr;
    v<v<int> > up;
    v<int> size;
    v<int> depth;
    v<int> pr;
    v<int> pos;
    v<int> a;
    v<int> start;
    seg_tree tr;
    int dfs(int v, int p) {
        depth[v] = depth[p] + 1;
        pr[v] = p;
        up[v][0] = p;
        for (int i = 1; i < max_up; ++i)
            up[v][i] = up[up[v][i - 1]][i - 1];
        int heavy = 0;
        for (int i = 0; i < gr[v].size(); ++i) {
            int to = gr[v][i].first;
            size[v] += dfs(to, v);
            if (size[to] > size[gr[v][heavy].first])
                heavy = i;
        }
        if (gr[v].size())
            std::swap(gr[v][0], gr[v][heavy]);
        return size[v];
    }
    void dfs2(int v, int x) {
        pos[v] = static_cast<int>(a.size());
        a.push_back(x);
        for (auto [to, w] : gr[v]) {
            if (2 * size[to] >= size[v])
                start[to] = start[v];
            else
                start[to] = to;
            dfs2(to, w);
        }
    }
    int lca(int a, int b) {
      if (depth[a] < depth[b]) std::swap(a, b);
        for (int i = max_up - 1; i >= 0; --i)
            if (depth[up[a][i]] >= depth[b])
                a = up[a][i];
        if (a == b) return a;
        for (int i = max_up - 1; i >= 0; --i)
            if (up[a][i] != up[b][i])
                a = up[a][i], b = up[b][i];
        return up[a][0];
    }
    int get_path(int v, int u) {
        int res = 1E9;
        for (; depth[start[v]] > depth[u]; v = pr[start[v]])
            res = std::min(tr.get(pos[start[v]], pos[v] + 1), res);
        return std::min(res, tr.get(pos[u] + 1, pos[v] + 1));
    }
public:
    hld(graph_t &gr_): gr{gr_} {
        build();
    }
    int get(int a, int b) {
        int ab = lca(a, b);
        int r1 = get_path(a, ab);
        int r2 = get_path(b, ab);
        return std::min(r1, r2);
    }
    void build() {
        depth.resize(gr.size());
        up.resize(gr.size(), v<int>(max_up));
        size.resize(gr.size(), 1);
        pr.resize(gr.size());
        pos.resize(gr.size());
        start.resize(gr.size());
        dfs(0, 0);
        dfs2(0, 0);
        tr = seg_tree(a);
    }
};

int main() {
#ifdef __APPLE__
  std::freopen(std::getenv("FINPATH"), "r", stdin);
  std::freopen(std::getenv("FOUTPATH"), "w", stdout);
#endif
    int n;
    std::cin >> n;
    gr.resize(n);
    for (int i = 1; i < n; ++i) {
        int x, y;
        std::cin >> x >> y;
        gr[x - 1].push_back({i, y});
    }
    hld d(gr);
    int m;
    std::cin >> m;
    for (int i = 0; i < m; ++i) {
        int x, y;
        std::cin >> x >> y;
        std::cout << d.get(x - 1, y - 1) << '\n';
    }
    return 0;
}
