#include <algorithm>
#include <iostream>
#include <vector>

struct train {
  std::int64_t b, e;
  std::int64_t t_km;
  std::int64_t t_st;
};

std::vector<std::vector<std::int64_t>> gr;
std::vector<bool> used;
std::vector<std::int64_t> order;
void dfs(std::int64_t v) {
  if (used[v])
    return;
  used[v] = 1;
  for (auto to : gr[v])
    dfs(to);
  order.push_back(v + 1);
}

int main(std::int64_t argc, char **argv) {
  std::int64_t n;
  std::cin >> n;
  std::vector<train> tr(n);
  std::vector<std::int64_t> st;
  for (std::int64_t i = 0; i < n; ++i) {
    train &t = tr[i];
    std::cin >> t.b >> t.e >> t.t_st >> t.t_km;
    st.push_back(t.b);
    st.push_back(t.e);
  }
  std::sort(st.begin(), st.end());
  std::unique(st.begin(), st.end());
  std::vector<std::vector<std::pair<std::int64_t, std::int64_t>>> tr_st(
      st.size());
  for (std::int64_t i = 0; i < n; ++i) {
    train &t = tr[i];
    for (std::int64_t j = 0; j < st.size(); ++j) {
      std::int64_t c_st = st[j];
      if (t.b <= c_st && c_st <= t.e) {
        tr_st[j].push_back({t.t_st + t.t_km * (c_st - t.b), i});
      }
    }
  }
  for (std::int64_t i = 0; i < st.size(); ++i)
    std::sort(tr_st[i].begin(), tr_st[i].end());
  gr.resize(n);
  used.resize(n);
  for (std::int64_t i = 0; i < st.size(); ++i) {
    for (std::int64_t l = 0, r = 0; r < tr_st[i].size();) {
      for (; r < tr_st[i].size() && tr_st[i][l].first == tr_st[i][r].first; ++r)
        ;
      if (r == tr_st[i].size())
        break;
      for (; l < r; ++l)
        gr[tr_st[i][l].second].push_back(tr_st[i][r].second);
    }
  }
  for (std::int64_t i = 0; i < n; ++i) {
    dfs(i);
  }
  for (std::int64_t i = n - 1; i >= 0; --i)
    std::cout << order[i] << " ";
}