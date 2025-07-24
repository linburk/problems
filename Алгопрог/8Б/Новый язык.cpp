#include "iostream"
#include "string"
#include "vector"

using std::vector, std::string, std::pair;

class LANGUAGE final {
private:
  vector<vector<int>> igraph, rigraph;
  vector<pair<int, int>> buffer_add;

private:
  vector<int> order;
  vector<int> member;
  vector<bool> used;
  int count = 0;
  void topsort(int v) {
    used[v] = 1;
    for (auto to : igraph[v])
      if (!used[to])
        topsort(to);
    order.push_back(v);
  }
  void set_member(int v) {
    member[v] = count;
    for (auto to : rigraph[v])
      if (!member[to])
        set_member(to);
  }
  bool condensate() {
    for (int i = 0; i < igraph.size(); ++i) {
      if (!used[i])
        topsort(i);
    }
    for (int i = (int)rigraph.size() - 1; i >= 0; --i) {
      if (!member[order[i]])
        ++count;
      set_member(order[i]);
    }
    bool res = true;
    for (int i = 0; i < igraph.size() / 2; ++i) {
      if (member[2 * i] == member[2 * i + 1])
        res = false;
    }
    count = 0;
    member.assign(member.size(), 0);
    used.assign(used.size(), 0);
    order.clear();
    return res;
  }

public:
  LANGUAGE(int n) {
    igraph.resize(2 * n);
    rigraph.resize(2 * n);
    member.resize(2 * n);
    used.resize(2 * n);
  }
  void add_rule(int i1, char t1, int i2, char t2, bool buffer = 0) {
    if (t1 == 'V') {
      if (t2 == 'V') {
        igraph[2 * i1].push_back(2 * i2);
        rigraph[2 * i2].push_back(2 * i1);
        if (buffer)
          buffer_add.push_back({2 * i1, 2 * i2});
      }
      if (t2 == 'C') {
        igraph[2 * i1].push_back(2 * i2 + 1);
        rigraph[2 * i2 + 1].push_back(2 * i1);
        if (buffer)
          buffer_add.push_back({2 * i1, 2 * i2 + 1});
      }
    }
    if (t1 == 'C') {
      if (t2 == 'V') {
        igraph[2 * i1 + 1].push_back(2 * i2);
        rigraph[2 * i2].push_back(2 * i1 + 1);
        if (buffer)
          buffer_add.push_back({2 * i1 + 1, 2 * i2});
      }
      if (t2 == 'C') {
        igraph[2 * i1 + 1].push_back(2 * i2 + 1);
        rigraph[2 * i2 + 1].push_back(2 * i1 + 1);
        if (buffer)
          buffer_add.push_back({2 * i1 + 1, 2 * i2 + 1});
      }
    }
  }
  void clear_buffer() {
    while (buffer_add.size())
      pop_buffer();
  }
  void pop_buffer() {
    igraph[buffer_add.back().first].pop_back();
    rigraph[buffer_add.back().second].pop_back();
    buffer_add.pop_back();
  }
  bool check_2sat() { return condensate(); }
};

int main(int argc, char **argv) {
#ifdef __APPLE__
  std::freopen("/Users/dmitrii/Documents/Code/Code/input.txt", "r", stdin);
  std::freopen("/Users/dmitrii/Documents/Code/Code/output.txt", "w", stdout);
#endif
  string alphabet;
  std::cin >> alphabet;
  int n, m;
  std::cin >> n >> m;
  LANGUAGE lang(n);
  for (int i = 0; i < m; ++i) {
    int i1, i2;
    char t1, t2;
    std::cin >> i1 >> t1 >> i2 >> t2;
    lang.add_rule(i1 - 1, t1, i2 - 1, t2);
  }
  string str;
  std::cin >> str;
  vector<char> ans(n);
  bool gl_can = 0;
  for (int i = n - 1; i >= 1 && !gl_can; --i) {
    for (int j = 0; j < i; ++j) {
      ans[j] = str[j];
      if (alphabet[str[j] - 'a'] == 'V') {
        lang.add_rule(j, 'C', j, 'V', 1);
      }
      if (alphabet[str[j] - 'a'] == 'C') {
        lang.add_rule(j, 'V', j, 'C', 1);
      }
    }
    for (int j = 0; j < i - 1; ++j) {
      if (alphabet[str[j] - 'a'] == 'V') {
        if (alphabet[str[j + 1] - 'a'] == 'V') {
          lang.add_rule(j, 'V', j + 1, 'V', 1);
          lang.add_rule(j + 1, 'V', j, 'V', 1);
        }
        if (alphabet[str[j + 1] - 'a'] == 'C') {
          lang.add_rule(j, 'V', j + 1, 'C', 1);
          lang.add_rule(j + 1, 'C', j, 'V', 1);
        }
      }
      if (alphabet[str[j] - 'a'] == 'C') {
        if (alphabet[str[j + 1] - 'a'] == 'V') {
          lang.add_rule(j, 'C', j + 1, 'V', 1);
          lang.add_rule(j + 1, 'V', j, 'C', 1);
        }
        if (alphabet[str[j + 1] - 'a'] == 'C') {
          lang.add_rule(j, 'C', j + 1, 'C', 1);
          lang.add_rule(j + 1, 'C', j, 'C', 1);
        }
      }
    }
    for (int k = i; k < n; ++k) {
      bool V = 0, C = 0;
      bool can = 0;
      for (int t = (k == i ? str[k] - 'a' + 1 : 0);
           t < alphabet.size() && (!V || !C); ++t) {
        bool force = 0;
        if (alphabet[t] == 'V' && !V) {
          force = 1;
          lang.add_rule(k, 'C', k, 'V', 1);
          if (k) {
            if (alphabet[ans[k - 1] - 'a'] == 'V') {
              lang.add_rule(k - 1, 'V', k, 'V', 1);
              lang.add_rule(k, 'V', k - 1, 'V', 1);
            }
            if (alphabet[ans[k - 1] - 'a'] == 'C') {
              lang.add_rule(k - 1, 'C', k, 'V', 1);
              lang.add_rule(k, 'V', k - 1, 'C', 1);
            }
          }
          V = 1;
        }
        if (alphabet[t] == 'C' && !C) {
          force = 1;
          lang.add_rule(k, 'V', k, 'C', 1);
          if (k) {
            if (alphabet[ans[k - 1] - 'a'] == 'V') {
              lang.add_rule(k - 1, 'V', k, 'C', 1);
              lang.add_rule(k, 'C', k - 1, 'V', 1);
            }
            if (alphabet[ans[k - 1] - 'a'] == 'C') {
              lang.add_rule(k - 1, 'C', k, 'C', 1);
              lang.add_rule(k, 'C', k - 1, 'C', 1);
            }
          }
          C = 1;
        }
        if (force) {
          ans[k] = t + 'a';
          bool check = lang.check_2sat();
          if (!check) {
            for (int p = 0; p < 5; ++p)
              lang.pop_buffer();
            continue;
          } else {
            can = 1;
            break;
          }
        }
      }
      if (!can)
        break;
      if (k == n - 1 && can) {
        gl_can = 1;
        break;
      }
    }
    lang.clear_buffer();
  }
  if (gl_can) {
    for (auto i : ans)
      std::cout << i;
  } else {
    std::cout << "-1\n";
  }
}