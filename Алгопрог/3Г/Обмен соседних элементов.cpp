#include <algorithm>
#include <iostream>
#include <vector>
int main(int argc, const char **argv) {
  int n;
  std::vector<int> arr;
  std::vector<std::pair<int, int>> to_sort;
  std::string str;

  std::cin >> n;
  arr.resize(n);
  for (int i = 0; i < n; ++i)
    std::cin >> arr[i];
  std::cin >> str;

  for (int l = 0, r = 0; l < n - 1;) {
    if (str[l] == '0') {
      ++l;
      continue;
    }
    r = l;
    while (r < n - 1 && str[r] == '1')
      ++r;
    to_sort.push_back({l, r});
    l = r;
  }

  for (auto [l, r] : to_sort) {
    std::sort(arr.begin() + l, arr.begin() + r + 1);
  }

  for (int i = 0; i < n - 1; ++i) {
    if (arr[i] > arr[i + 1]) {
      std::cout << "NO\n";
      return 0;
    }
  }

  std::cout << "YES\n";
  return 0;
}