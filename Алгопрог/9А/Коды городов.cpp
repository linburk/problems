#include <cmath>
#include <iostream>
#include <list>
#include <vector>

std::vector<std::string> cities;
std::vector<int> answer;
int n, m;

class trie {
  struct node_t {
    int terminal_id = -1;
    std::list<std::pair<int, node_t *>> next;
  } m_root;

  void p_insert(std::string &num, int id, int pos, node_t *node) {
    if (pos == num.size()) {
      node->terminal_id = id;
      return;
    }
    node_t *to = nullptr;
    for (auto it = node->next.begin(); it != node->next.end(); it++) {
      if (it->first == num[pos] - '0') {
        to = it->second;
        break;
      }
    }
    if (!to) {
      to = new node_t{};
      node->next.push_back(std::make_pair(num[pos] - '0', to));
    }
    p_insert(num, id, pos + 1, to);
  }

  int p_dfs(node_t *node, int depth) {
    int min_depth = INT_MAX;
    if (node->terminal_id != -1) {
      answer[node->terminal_id] = std::pow(10, m - depth);
      min_depth = depth;
    }
    for (auto it = node->next.begin(); it != node->next.end(); it++) {
      int to_depth = p_dfs(it->second, depth + 1);
      if (node->terminal_id != -1) {
        answer[node->terminal_id] -= std::pow(10, m - to_depth);
      }
      min_depth = std::min(min_depth, to_depth);
    }
    return min_depth;
  }

public:
  void insert(std::string &num, int id) {
    return p_insert(num, id, 0, &m_root);
  }
  int dfs() { return p_dfs(&m_root, 0); }
};

int main(int argc, char **argv) {
  std::cin >> n >> m;
  cities.resize(n);
  answer.resize(n);
  trie bor;
  for (int i = 0; i < n; i++) {
    std::string num, city;
    std::cin >> num >> city;
    bor.insert(num, i);
    cities[i] = city;
  }
  bor.dfs();
  for (int i = 0; i < n; i++) {
    std::cout << cities[i] << " " << answer[i] << "\n";
  }
  return 0;
}