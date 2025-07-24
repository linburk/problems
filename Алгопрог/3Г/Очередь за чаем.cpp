#include <iostream>

int main(int argc, const char **argv) {
  int t;
  std::cin >> t;
  for (; t--;) {
    int n;
    std::cin >> n;
    int last_st = 0;
    for (int i = 0; i < n; ++i) {
      int l, r;
      std::cin >> l >> r;
      if (l > last_st) {
        last_st = l;
      } else if (r > last_st) {
        ++last_st;
      } else {
        std::cout << "0\n";
        continue;
      }
      std::cout << last_st << " ";
    }
    std::cout << "\n";
  }
}