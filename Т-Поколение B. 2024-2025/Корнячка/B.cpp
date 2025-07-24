#include <algorithm>
#include <iostream>
#include <vector>

struct query {
    int l, r;
};

int const BLOCK_SZ = 555;

using i64 = long long;

int main()
{
#ifdef __APPLE__
    std::freopen("input.txt", "r", stdin);
    std::freopen("output.txt", "w", stdout);
#else
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
#endif
    int n, t;
    std::cin >> n >> t;
    std::vector<int> a(n);
    std::vector<query> q(t);
    std::vector<std::vector<int>> block(n / BLOCK_SZ + 1);
    for (auto&& i : a) {
        std::cin >> i;
    }
    for (int i = 0; i < t; ++i) {
        auto&& [l, r] = q[i];
        std::cin >> l >> r;
        --l;
        --r;
        block[l / BLOCK_SZ].push_back(i);
    }
    std::vector<i64> ans(t);
    std::vector<int> count(1E6 + 1);
    i64 sum = 0;
    auto add = [&](int i) {
        sum -= 1LL * count[a[i]] * count[a[i]] * a[i];
        ++count[a[i]];
        sum += 1LL * count[a[i]] * count[a[i]] * a[i];
    };
    auto del = [&](int i) {
        sum -= 1LL * count[a[i]] * count[a[i]] * a[i];
        --count[a[i]];
        sum += 1LL * count[a[i]] * count[a[i]] * a[i];
    };
    for (int i = 0, l = 0, r = -1; i < block.size(); ++i) {
        if (block[i].empty())
            continue;
        std::sort(block[i].begin(), block[i].end(), [&q](int lhs, int rhs) {
            if (q[lhs].r == q[rhs].r)
                return lhs < rhs;
            return q[lhs].r < q[rhs].r;
        });
        for (; l > BLOCK_SZ * i;)
            del(l--);
        for (; r > BLOCK_SZ * i;)
            del(r--);
        for (int j = 0; j < block[i].size(); ++j) {
            auto [ql, qr] = q[block[i][j]];
            for (; r < qr;)
                add(++r);
            for (; l < ql;)
                del(l++);
            for (; l > ql;)
                add(--l);
            ans[block[i][j]] = sum;
        }
    }
    for (int i = 0; i < t; ++i) {
        std::cout << ans[i] << '\n';
    }
}
