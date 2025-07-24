#include <iostream>
#include <vector>

int const max_up = 20;
int       n;
int       m;

std::vector<std::vector<int>> graph;
std::vector<std::vector<int>> up;
std::vector<int>              depth;

void dfs(int v, int p) {
    depth[v] = depth[p] + 1;
    up[v][0] = p;
    for (int i = 1; i < max_up; ++i)
        up[v][i] = up[up[v][i - 1]][i - 1];
    for (auto to : graph[v]) {
        if (to != p)
            dfs(to, v);
    }
}

int lca(int a, int b) {
    if (depth[a] < depth[b])
        std::swap(a, b);
    for (int i = max_up - 1; i >= 0; --i) {
        if (depth[up[a][i]] >= depth[b])
            a = up[a][i];
    }
    if (a == b)
        return a;
    for (int i = max_up - 1; i >= 0; --i) {
        if (up[a][i] != up[b][i]) {
            a = up[a][i];
            b = up[b][i];
        }
    }
    return up[a][0];
}

int main(void) {
    for (;;) {
        std::cin >> n;
        if (n == 0)
            break;
        graph.resize(n);
        up.resize(n, std::vector<int>(max_up, 0));
        depth.resize(n, 0);
        for (int i = 1; i < n; ++i) {
            int a, b;
            std::cin >> a >> b;
            --a, --b;
            graph[a].push_back(b);
            graph[b].push_back(a);
        }
        dfs(0, 0);
        int root = 0;
        std::cin >> m;
        for (int i = 0; i < m; ++i) {
            char c;
            std::cin >> c;
            if (c == '!') {
                int u;
                std::cin >> u;
                --u;
                root = u;
            } else if (c == '?') {
                int u, v;
                std::cin >> u >> v;
                --u, --v;
                int a = lca(u, root);
                int b = lca(v, root);
                int c = lca(v, u);
                if (depth[a] > depth[c])
                    c = a;
                if (depth[b] > depth[c])
                    c = b;
                std::cout << c + 1 << '\n';
            }
        }
        graph.clear();
        up.clear();
        depth.clear();
    }
    return 0;
}
