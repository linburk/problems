#include <functional>
#include <iostream>
#include <vector>

int main()
{
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> mv(2);
    int k1, k2;
    std::cin >> k1;
    mv[0].resize(k1);
    for (int i = 0; i < k1; ++i)
        std::cin >> mv[0][i];
    std::cin >> k2;
    mv[1].resize(k2);
    for (int i = 0; i < k2; ++i)
        std::cin >> mv[1][i];
    std::vector<std::vector<int>> count(2, std::vector<int>(n));
    std::vector<std::vector<int>> res(2, std::vector<int>(n));
    std::function<void(int, int, int)> dfs = [&](int pos, int pl, int cond) {
        if (res[pl][pos])
            return;
        res[pl][pos] = cond;
        int n_pl = pl ^ 1;
        int n_cond = cond ^ 3;
        for (auto d : mv[n_pl])
        {
            int n_pos = (pos - d + n) % n;
            if (cond == 1 || (++count[n_pl][n_pos] == mv[n_pl].size()))
            {
                dfs(n_pos, n_pl, n_cond);
            }
        }
    };
    res[1][0] = 1;
    dfs(0, 0, 1);
    res[1][0] = 0;
    dfs(0, 1, 1);
    for (int i = 0; i < 2; ++i)
    {
        for (int j = 1; j < n; ++j)
        {
            if (res[i][j] == 1)
            {
                std::cout << "Lose";
            }
            else if (res[i][j] == 2)
            {
                std::cout << "Win";
            }
            else
            {
                std::cout << "Loop";
            }
            std::cout << " \n"[j == n - 1];
        }
    }
    return 0;
}
