#include <algorithm>
#include <array>
#include <chrono>
#include <memory>
#include <random>
#include <unordered_map>
#include <vector>

int const MAX_N = 1E6 + 1;
int const MAX_UP = 21;

std::mt19937 ru32(std::chrono::steady_clock().now().time_since_epoch().count());

std::array<int, MAX_N> size;
std::array<int, MAX_N> depth;
std::array<std::array<int, MAX_UP>, MAX_N> up;
std::array<int, MAX_N> start;
std::array<std::vector<int>, MAX_N> path;
std::array<std::vector<int>, MAX_N> graph;
int root;

std::unique_ptr<std::vector<int>> a;

template <typename T> struct ordered_set
{
  private:
    struct node
    {
        int key_;
        unsigned int priority;
        int size = 1;
        node *left = nullptr;
        node *right = nullptr;
        node() : priority{ru32()}
        {
        }
        node(int key) : node()
        {
            key_ = key;
        }
    } *root = nullptr;
    using p_node = std::pair<node *, node *>;
    int inline n_size(node const *n) const
    {
        return n ? n->size : 0;
    }
    void inline n_update(node *n)
    {
        n ? n->size = n_size(n->left) + 1 + n_size(n->right) : 0;
    }
    p_node split(int key, node *n)
    {
        p_node res;
        if (n == nullptr)
        {
            return res;
        }
        else if (n->key_ < key)
        {
            p_node t = split(key, n->right);
            n->right = t.first;
            res.second = t.second;
            res.first = n;
        }
        else
        {
            p_node t = split(key, n->left);
            n->left = t.second;
            res.first = t.first;
            res.second = n;
        }
        n_update(n);
        return res;
    }
    node *merge(node *l, node *r)
    {
        if (l && r)
        {
            if (l->priority > r->priority)
            {
                l->right = merge(l->right, r);
                n_update(l);
                return l;
            }
            else
            {
                r->left = merge(l, r->left);
                n_update(r);
                return r;
            }
        }
        else if (l)
        {
            return l;
        }
        else if (r)
        {
            return r;
        }
        else
        {
            return nullptr;
        }
    }

  public:
    int size() const
    {
        return n_size(root);
    };
    int order_of_key(int key)
    {
        p_node t = split(key, root);
        int res = n_size(t.first);
        root = merge(t.first, t.second);
        return res;
    }
    void erase(int key)
    {
        p_node t = split(key, root);
        p_node t2 = split(key + 1, t.second);
        delete t2.first;
        root = merge(t.first, t2.second);
    }
    void insert(int key)
    {
        p_node t = split(key, root);
        node *n = new node(key);
        n = merge(t.first, n);
        root = merge(n, t.second);
    }
};

std::array<std::unordered_map<int, ordered_set<int>>, MAX_N> up_path, down_path;

void dfs0(int v, int p)
{
    size[v] = 1;
    depth[v] = depth[p] + 1;
    up[v][0] = p;
    for (int i = 1; i < MAX_UP; ++i)
        up[v][i] = up[up[v][i - 1]][i - 1];
    int max_v = 0;
    for (int i = 0; i < graph[v].size(); ++i)
    {
        int to = graph[v][i];
        dfs0(to, v);
        size[v] += size[to];
        if (size[to] > size[graph[v][max_v]])
            max_v = i;
    }
    if (graph[v].size())
        std::swap(graph[v][0], graph[v][max_v]);
}

void dfs1(int v)
{
    if (graph[v].empty())
        return;
    start[graph[v][0]] = start[v];
    path[start[v]].push_back(graph[v][0]);
    dfs1(graph[v][0]);
    for (int i = 1; i < graph[v].size(); ++i)
    {
        int to = graph[v][i];
        start[to] = to;
        path[to].push_back(to);
        dfs1(to);
    }
}

int get_lca(int a, int b)
{
    if (depth[a] < depth[b])
        std::swap(a, b);
    for (int i = MAX_UP - 1; i >= 0; --i)
    {
        if (depth[up[a][i]] >= depth[b])
            a = up[a][i];
    }
    if (a == b)
        return a;
    for (int i = MAX_UP - 1; i >= 0; --i)
    {
        if (up[a][i] != up[b][i])
            a = up[a][i], b = up[b][i];
    }
    return up[a][0];
}

void update(int v, int val = -1)
{
    int i = start[v];
    int j = depth[v] - depth[start[v]];
    if (val != -1) [[likely]]
    {
        int p_val = a->at(v);
        down_path[i][j - p_val].erase(j);
        up_path[i][(path[i].size() - 1 - j) - p_val].erase(path[i].size() - 1 - j);
        a->at(v) = val;
    }
    else
    {
        val = a->at(v);
    }
    down_path[i][j - val].insert(j);
    up_path[i][(path[i].size() - 1 - j) - val].insert(path[i].size() - 1 - j);
}

void build(int n)
{
    for (int v = 0; v < n; ++v)
    {
        update(v);
    }
}
int get_up_path(int a, int lca)
{
    int res = 0;
    int length = 0;
    int i, lca_pos, a_pos;
    for (; depth[start[a]] > depth[lca]; a = up[i][0])
    {
        i = start[a];
        a_pos = path[i].size() - 1 - (depth[a] - depth[i]);
        res += up_path[i][-(length - a_pos)].size() - up_path[i][-(length - a_pos)].order_of_key(a_pos);
        length += path[i].size() - a_pos;
    }
    i = start[a];
    lca_pos = path[i].size() - 1 - (depth[lca] - depth[i]);
    a_pos = path[i].size() - 1 - (depth[a] - depth[i]);
    res += up_path[i][-(length - a_pos)].order_of_key(lca_pos + 1) - up_path[i][-(length - a_pos)].order_of_key(a_pos);
    return res;
}

int get_down_path(int lca, int b, int length)
{
    int res = 0;
    int i, lca_pos, b_pos;
    for (; depth[start[b]] > depth[lca]; b = up[i][0])
    {
        i = start[b];
        b_pos = depth[b] - depth[i];
        res += down_path[i][-(length - 1 - b_pos)].order_of_key(b_pos + 1);
        length -= b_pos + 1;
    }
    i = start[b];
    lca_pos = depth[lca] - depth[i];
    b_pos = depth[b] - depth[i];
    res += down_path[i][-(length - 1 - b_pos)].order_of_key(b_pos + 1) -
           down_path[i][-(length - 1 - b_pos)].order_of_key(lca_pos);
    return res;
}

int get(int a, int b)
{
    int lca = get_lca(a, b);
    int res = 0;
    res += get_up_path(a, lca);
    res += get_down_path(lca, b, depth[b] + depth[a] - 2 * depth[lca] + 1);
    if (::a->at(lca) == depth[a] - depth[lca])
        --res;
    return res;
}

std::vector<int> solve(int n, int q, std::vector<int> a, std::vector<int> p, std::vector<int> qt, std::vector<int> qx,
                       std::vector<int> qy)
{
    std::vector<int> res;
    res.reserve(q);
    ::a = std::make_unique<std::vector<int>>(a);
    for (int i = 0; i < n; ++i)
    {
        if (p[i] == -1)
        {
            root = i;
        }
        else
        {
            graph[p[i]].push_back(i);
        }
    }
    dfs0(root, root);
    start[root] = root;
    path[root].push_back(root);
    dfs1(root);
    build(n);
    for (int i = 0; i < q; ++i)
    {
        if (qt[i] == 1)
        {
            update(qx[i], qy[i]);
        }
        else
        {
            res.push_back(get(qx[i], qy[i]));
        }
    }
    return res;
}

#if __APPLE__
#include <iostream>
int main()
{
    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n), p(n), qt(q), qx(q), qy(q);
    for (int i = 0; i < n; ++i)
    {
        std::cin >> a[i];
    }
    for (int i = 0; i < n; ++i)
    {
        std::cin >> p[i];
    }
    for (int i = 0; i < q; ++i)
    {
        std::cin >> qt[i] >> qx[i] >> qy[i];
    }
    auto res = solve(n, q, a, p, qt, qx, qy);
    std::cout << std::endl;
    for (int i = 0; i < res.size(); ++i)
    {
        std::cout << res[i] << std::endl;
    }
    return 0;
}
#endif
