#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

struct ps_tree {
  private:
    struct node {
        int value = 0;
        int left = 0;
        int right = 0;
    };
    std::vector<node> tree;
    int               size;

    int add(int pos, int value, int lb, int rb, int n) {
        tree.push_back(tree[n]);
        n = static_cast<int>(tree.size()) - 1;
        if (lb == rb - 1) {
            tree[n].value += value;
            return n;
        }
        int mb = (lb + rb) >> 1;
        if (pos < mb) {
            tree[n].left = add(pos, value, lb, mb, tree[n].left);
        } else {
            tree[n].right = add(pos, value, mb, rb, tree[n].right);
        }
        tree[n].value = tree[tree[n].left].value + tree[tree[n].right].value;
        return n;
    }
    int get(int lq, int rq, int lb, int rb, int n) {
        if (lb >= rq || rb <= lq)
            return 0;
        if (lq <= lb && rb <= rq)
            return tree[n].value;
        int mb = (lb + rb) >> 1;
        return get(lq, rq, lb, mb, tree[n].left) +
               get(lq, rq, mb, rb, tree[n].right);
    }

  public:
    ps_tree() {}
    ps_tree(int size_) : size{size_} {
        tree.reserve(10 * size);
        tree.emplace_back();
    }
    int add(int pos, int val, int root_) {
        return add(pos, val, 0, size, root_);
    }
    int get(int lq, int rq, int root_) { return get(lq, rq, 0, size, root_); }
};

ps_tree tr;

int const max_up = 20;
int       n;
int       q;

std::vector<std::vector<std::pair<int, int>>> graph;
std::vector<std::vector<int>>                 up;
std::vector<int>                              depth;
std::vector<int>                              version;
std::vector<int>                              values;

std::unordered_map<int, int> value_pos;

void dfs(int v, int p, int x) {
    version[v] = tr.add(value_pos[x], 1, version[p]);
    depth[v] = depth[p] + 1;
    up[v][0] = p;
    for (int i = 1; i < max_up; ++i) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    for (auto [to, x_] : graph[v]) {
        if (to != p)
            dfs(to, v, x_);
    }
}

int lca(int u, int v) {
    if (depth[u] < depth[v])
        std::swap(u, v);
    for (int i = max_up - 1; i >= 0; --i) {
        if (depth[up[u][i]] >= depth[v])
            u = up[u][i];
    }
    if (u == v)
        return u;
    for (int i = max_up - 1; i >= 0; --i) {
        if (up[u][i] != up[v][i]) {
            u = up[u][i];
            v = up[v][i];
        }
    }
    return up[v][0];
}

int count(int u, int v, int x) {
    int uv = lca(u, v);
    x = *std::upper_bound(values.begin(), values.end(), x);
    return tr.get(0, value_pos[x], version[v]) +
           tr.get(0, value_pos[x], version[u]) -
           2 * tr.get(0, value_pos[x], version[uv]);
}

int main(void) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cin >> n >> q;
    graph.resize(n);
    version.resize(n);
    depth.resize(n);
    up.resize(n, std::vector<int>(max_up));
    values.push_back(1E9);
    for (int i = 1; i < n; ++i) {
        int s, f, l;
        std::cin >> s >> f >> l;
        --s, --f;
        graph[s].push_back({f, l});
        graph[f].push_back({s, l});
        values.push_back(l);
    }
    std::sort(values.begin(), values.end());
    values.erase(std::unique(values.begin(), values.end()), values.end());
    for (int i = 0; i < values.size(); ++i) {
        value_pos[values[i]] = i;
    }
    tr = ps_tree(static_cast<int>(values.size()));
    dfs(0, 0, 1E9);
    for (int i = 0; i < q; ++i) {
        int a, b, x;
        std::cin >> a >> b >> x;
        --a, --b;
        std::cout << count(a, b, x) << "\n";
    }
    return 0;
}
