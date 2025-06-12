#include <iostream>
#include <string>

class trie {
  struct node_t {
    bool terminate = false;
    node_t *next[26];
    node_t() {
      for (int i = 0; i < 26; i++)
        next[i] = nullptr;
    }
  } m_root;

  void p_insert(std::string &str, size_t pos, node_t *node) {
    if (pos == str.size()) {
      node->terminate = true;
      return;
    }
    if (!node->next[str[pos] - 'a']) {
      node->next[str[pos] - 'a'] = new node_t();
    }
    p_insert(str, pos + 1, node->next[str[pos] - 'a']);
  }

  int p_dfs(node_t *node) {
    int max_res = node->terminate;
    for (int i = 0; i < 26; i++) {
      if (node->next[i])
        max_res = std::max(p_dfs(node->next[i]) + node->terminate, max_res);
    }
    return max_res;
  }

public:
  void insert(std::string &str) { return p_insert(str, 0, &m_root); }
  int dfs() { return p_dfs(&m_root); }
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
  std::cout << bor.dfs() << "\n";
}