#include <iostream>
#include <set>
#include <vector>

int const max_up = 21;
int       n;
int       m;

std::vector<std::vector<int> > gr;
std::vector<int>               depth;

std::vector<std::vector<bool> > up_from;
std::vector<std::vector<bool> > up_to;
std::vector<std::vector<int> >  up;

std::set<std::pair<int, int> > edges;

void
dfs (int v, int p)
{
  depth[v] = depth[p] + 1;
  up[v][0] = p;
  if (edges.count ({ p, v }))
    up_to[v][0] = 1;
  if (edges.count ({ v, p }))
    up_from[v][0] = 1;
  for (int i = 1; i < max_up; ++i)
    {
      up[v][i]      = up[up[v][i - 1]][i - 1];
      up_to[v][i]   = up_to[v][i - 1] & up_to[up[v][i - 1]][i - 1];
      up_from[v][i] = up_from[v][i - 1] & up_from[up[v][i - 1]][i - 1];
    }
  for (auto to : gr[v])
    {
      if (to != p)
        dfs (to, v);
    }
}

bool
can (int a, int b)
{
  bool res = 1;
  if (depth[a] >= depth[b])
    {
      for (int i = max_up - 1; i >= 0; --i)
        {
          if (depth[up[a][i]] >= depth[b])
            {
              res &= up_from[a][i];
              a = up[a][i];
            }
        }
    }
  else
    {
      for (int i = max_up - 1; i >= 0; --i)
        {
          if (depth[up[b][i]] >= depth[a])
            {
              res &= up_to[b][i];
              b = up[b][i];
            }
        }
    }
  if (a == b)
    return res;
  for (int i = max_up - 1; i >= 0; --i)
    {
      if (up[a][i] != up[b][i])
        {
          res &= up_from[a][i];
          res &= up_to[b][i];
          a = up[a][i];
          b = up[b][i];
        }
    }
  return res & up_from[a][0] & up_to[b][0];
}

int
main (void)
{
  std::cin >> n;
  gr.resize (n);
  up_from.resize (n, std::vector<bool> (max_up));
  up_to.resize (n, std::vector<bool> (max_up));
  up.resize (n, std::vector<int> (max_up));
  depth.resize (n);
  for (int i = 1; i < n; ++i)
    {
      int a, b;
      std::cin >> a >> b;
      --a, --b;
      edges.insert ({ a, b });
      gr[a].push_back (b);
      gr[b].push_back (a);
    }
  up_to[0][0] = up_from[0][0] = 1;
  dfs (0, 0);
  std::cin >> m;
  for (int i = 0; i < m; ++i)
    {
      int x, y;
      std::cin >> x >> y;
      --x, --y;
      std::cout << (can (x, y) ? "Yes\n" : "No\n");
    }
  return 0;
}
