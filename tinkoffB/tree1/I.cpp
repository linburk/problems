#include <iostream>
#include <vector>

int const max_up = 20;
int       n;

std::vector<std::vector<int>> graph;
std::vector<std::vector<int>> up;
std::vector<int>              depth;

void add_vertex(int v, int p) {
    depth[v] = depth[p] + 1;
    up[v][0] = p;
    for (int i = 1; i < max_up; ++i)
        up[v][i] = up[up[v][i - 1]][i - 1];
}

int lca(int v, int u) {
    if (depth[v] <= depth[u])
        std::swap(v, u);
    for (int i = max_up - 1; i >= 0; --i) {
        if (depth[up[v][i]] >= depth[u])
            v = up[v][i];
    }
    if (v == u)
        return v;
    for (int i = max_up - 1; i >= 0; --i) {
        if (up[v][i] != up[u][i]) {
            v = up[v][i];
            u = up[u][i];
        }
    }
    return up[v][0];
}

int dist(int v, int u) { return depth[v] + depth[u] - 2 * depth[lca(u, v)]; }

int main(void) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cin >> n;
    ++n;
    graph.resize(n);
    up.resize(n, std::vector<int>(max_up));
    depth.resize(n);
    int max1 = 0;
    int max2 = 0;
    int max_val = 0;
    for (int i = 1; i < n; ++i) {
        int p;
        std::cin >> p;
        --p;
        add_vertex(i, p);
        int d1 = dist(i, max1);
        int d2 = dist(i, max2);
        if (d1 >= d2 && d1 > max_val) {
            max2 = i;
            max_val = d1;
        }
        if (d2 >= d1 && d2 > max_val) {
            max1 = i;
            max_val = d2;
        }
        std::cout << max_val << "\n";
    }
}
