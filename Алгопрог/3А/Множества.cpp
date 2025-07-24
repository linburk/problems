#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using i64 = long long;

int main(int argc, char **argv) {
  int n, m, k;
  std::cin >> n >> m >> k;
  std::vector<std::set<i64>> multiset(m + 1);
  std::map<i64, std::set<int>> contains;
  for (int i = 0; i < k; ++i) {
    i64 s, e;
    std::string COM;
    std::cin >> COM;
    if (COM == "ADD") {
      std::cin >> s >> e;
      multiset[s].insert(e);
      contains[e].insert(s);
    }
    if (COM == "DELETE") {
      std::cin >> s >> e;
      multiset[s].erase(e);
      contains[e].erase(s);
    }
    if (COM == "CLEAR") {
      std::cin >> s;
      for (auto el : multiset[s]) {
        contains[el].erase(s);
      }
      multiset[s].clear();
    }
    if (COM == "LISTSET") {
      std::cin >> s;
      for (auto el : multiset[s]) {
        std::cout << el << " ";
      }
      if (multiset[s].empty()) {
        std::cout << "-1";
      }
      std::cout << "\n";
    }
    if (COM == "LISTSETOF") {
      std::cin >> e;
      for (auto se : contains[e]) {
        std::cout << se << " ";
      }
      if (contains[e].empty()) {
        std::cout << "-1";
      }
      std::cout << "\n";
    }
  }
  return 0;
}