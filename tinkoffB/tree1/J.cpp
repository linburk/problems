#include <iostream>
#include <vector>

int const                     max_up = 20;
int                           n;
int                           m;
std::vector<std::vector<int>> graph;
std::vector<std::vector<int>> up;
std::vector<int>              depth;
int                           xor_ = 0;

void dfs(int v, int p) {
    depth[v] = depth[p] + 1;
    up[v][0] = p;
    for (int i = 1; i < max_up; ++i)
        up[v][i] = up[up[v][i - 1]][i - 1];
    for (auto to : graph[v])
        dfs(to, v);
}

int lca(int u, int v) {
    if (depth[u] > depth[v])
        std::swap(u, v);
    for (int i = max_up - 1; i >= 0; --i) {
        if (depth[up[v][i]] >= depth[u])
            v = up[v][i];
    }
    if (u == v)
        return v;
    for (int i = max_up - 1; i >= 0; --i) {
        if (up[v][i] != up[u][i]) {
            v = up[v][i];
            u = up[u][i];
        }
    }
    return up[v][0];
}

int dist(int u, int v) { return depth[u] + depth[v] - 2 * depth[lca(u, v)]; }

int get_path(int u, int v) {
    int d = dist(u, v) + 1;
    return (d & 1 ? xor_ : 0);
}

int main(void) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cin >> n >> m;
    graph.resize(n);
    depth.resize(n);
    up.resize(n, std::vector<int>(max_up));
    for (int i = 1; i < n; ++i) {
        int p;
        std::cin >> p;
        --p;
        graph[p].push_back(i);
    }
    dfs(0, 0);
    for (int i = 0; i < m; ++i) {
        int type;
        std::cin >> type;
        if (type == 1) {
            int a, b;
            std::cin >> a >> b;
            --a, --b;
            std::cout << get_path(a, b) << '\n';
        } else if (type == 2) {
            int x;
            std::cin >> x;
            xor_ ^= x;
        }
    }
}
