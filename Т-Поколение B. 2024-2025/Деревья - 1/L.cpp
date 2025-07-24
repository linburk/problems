#include <iostream>
#include <vector>

struct s_tree {
    std::vector<int> tree;
    int              size;

    void add(int l, int r, int val) {
        l += size;
        r += size;
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1)
                tree[l++] += val;
            if (r & 1)
                tree[--r] += val;
        }
    }
    int get(int pos) {
        pos += size;
        int res = 0;
        for (; pos; pos >>= 1) {
            res += tree[pos];
        }
        return res;
    }
    s_tree(int size_) : size{size_} { tree.resize(2 * size); }
    s_tree() {}
} tree;

int const max_up = 20;
int       n;
int       m;

std::vector<std::vector<int>> graph;
std::vector<std::vector<int>> up;
std::vector<int>              depth;
std::vector<int>              tour;
std::vector<int>              size;
std::vector<int>              in;
std::vector<int>              out;

void dfs(int v, int p) {
    in[v] = static_cast<int>(tour.size());
    tour.push_back(v);
    depth[v] = depth[p] + 1;
    up[v][0] = p;
    for (int i = 1; i < max_up; ++i) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    for (auto to : graph[v]) {
        if (to != p) {
            dfs(to, v);
            size[v] += size[to];
        }
    }
    out[v] = in[v] + size[v];
}

int lca(int v, int u) {
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

void query(int x, int y) {
    if (depth[x] > depth[y])
        std::swap(x, y);
    int xy = lca(x, y);
    if (xy == x) {
        tree.add(in[0], out[0], 1);
        if (up[y][0] != x) {
            tree.add(in[y], out[y], 1);
            for (int i = max_up - 1; i >= 0; --i) {
                if (depth[up[y][i]] > depth[xy])
                    y = up[y][i];
            }
            tree.add(in[y], out[y], -1);
        }
    } else {
        tree.add(in[x], out[x], 1);
        tree.add(in[y], out[y], 1);
    }
}

int main(void) {
    std::cin >> n;
    tree = s_tree(n);
    graph.resize(n);
    up.resize(n, std::vector<int>(max_up));
    in.resize(n);
    out.resize(n);
    depth.resize(n);
    size.resize(n, 1);
    for (int i = 1; i < n; ++i) {
        int x, y;
        std::cin >> x >> y;
        --x, --y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    dfs(0, 0);
    std::cin >> m;
    for (int i = 0; i < m; ++i) {
        int x, y;
        std::cin >> x >> y;
        --x, --y;
        query(x, y);
    }
    int res = 0;
    for (int i = 0; i < n; ++i) {
        res = std::max(res, tree.get(in[i]));
    }
    std::cout << res << "\n";
    return 0;
}
