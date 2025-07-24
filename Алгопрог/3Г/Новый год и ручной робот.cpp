#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, const char **argv) {
  int sx, sy;
  int res = 0;
  int n, m;
  std::vector<std::vector<char>> t;
  std::string COM;
  std::cin >> n >> m;
  t.resize(n, std::vector<char>(m));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      std::cin >> t[i][j];
      if (t[i][j] == 'S')
        sx = i, sy = j;
    }
  }
  std::cin >> COM;
  std::string perm = "0123";
  for (int i = 0; i < 24; ++i) {
    int px = sx, py = sy;
    char dest = 0;
    for (int j = 0; j < COM.size(); ++j) {
      int c = perm[COM[j] - '0'] - '0';
      px += (c == 0) - (c == 1);
      py += (c == 2) - (c == 3);
      if (px < 0 || px >= n || py < 0 || py >= m)
        break;
      if (t[px][py] == '#')
        break;
      if (t[px][py] == 'E')
        dest = 1;
    }
    if (dest)
      ++res;
    std::next_permutation(perm.begin(), perm.end());
  }
  std::cout << res << "\n";
  return 0;
}