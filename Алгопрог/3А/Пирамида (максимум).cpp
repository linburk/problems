#include <functional>
#include <iostream>
#include <set>
#include <string>
using i64 = long long;

int main(int argc, char **argv) {
  std::multiset<i64, std::greater<i64>> heap;
  for (std::string COM; std::cin >> COM;) {
    i64 n;
    if (COM == "CLEAR") {
      heap.clear();
    }
    if (COM == "ADD") {
      std::cin >> n;
      heap.insert(n);
    }
    if (COM == "EXTRACT") {
      if (heap.empty()) {
        std::cout << "CANNOT\n";
        continue;
      }
      std::cout << *heap.begin() << "\n";
      heap.erase(heap.begin());
    }
  }
  return 0;
}