#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

std::vector<char> oper;

class trie {
  struct node_t {
    int terminate = 0;
    int max_length = 0;
    node_t *next[26];
    node_t() {
      for (int i = 0; i < 26; i++)
        next[i] = nullptr;
    }
  } m_root;

  void p_insert(std::string &str, size_t pos, node_t *node) {
    if (pos == str.size()) {
      node->terminate++;
      return;
    }
    if (!node->next[str[pos] - 'a']) {
      node->next[str[pos] - 'a'] = new node_t();
    }
    p_insert(str, pos + 1, node->next[str[pos] - 'a']);
    node->max_length =
        std::max(node->max_length, node->next[str[pos] - 'a']->max_length + 1);
  }

  void p_dfs(node_t *node) {
    for (; node->terminate; node->terminate--) {
      oper.push_back('P');
    }
    std::vector<int> order;
    for (int i = 0; i < 26; i++) {
      if (node->next[i]) {
        order.push_back(i);
      }
    }
    std::sort(order.begin(), order.end(), [&](int a, int b) {
      return node->next[a]->max_length < node->next[b]->max_length;
    });
    for (auto i : order) {
      oper.push_back('a' + i);
      p_dfs(node->next[i]);
    }
    oper.push_back('-');
  }

public:
  void insert(std::string &str) { return p_insert(str, 0, &m_root); }
  void dfs() { return p_dfs(&m_root); }
};

int main(int argc, char **argv) {
  int n;
  std::cin >> n;
  trie bor;
  for (int i = 0; i < n; i++) {
    std::string str;
    std::cin >> str;
    bor.insert(str);
  }
  bor.dfs();
  while (oper.back() == '-')
    oper.pop_back();
  std::cout << oper.size() << "\n";
  for (int i = 0; i < oper.size(); i++) {
    std::cout << oper[i] << "\n";
  }
}