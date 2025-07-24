#include <algorithm>
#include <iostream>
#include <vector>

using std::cin, std::cout, std::vector;
using i64 = long long;

struct query {
    int l, r;
};

// ZAVOZ

void solve()
{
    int n, q_;
    cin >> n >> q_;
    vector<int> a(n);
    vector<query> q(q_);
    int MAXA = 1;
    int const BSZ = 555;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        MAXA = std::max(MAXA, a[i] + 1);
    }
    vector<vector<int>> block(n / BSZ + 1);
    for (int i = 0; i < q_; ++i) {
        cin >> q[i].l >> q[i].r;
        --q[i].l, --q[i].r;
        block[q[i].r / BSZ].push_back(i);
    }
    vector<i64> ans(q_);
    vector<i64> len(n);
    len[0] = 1;
    for (int i = 1; i < n; ++i) {
        len[i] = len[i - 1] + 1LL * (i + 1) * (i + 2) / 2;
    }
    vector<int> count(MAXA);
    vector<i64> ld(MAXA);
    i64 mth = 0;
    i64 val = 0;
    auto addl = [&](int pos, int r) {
        ++count[a[pos]];
        ld[a[pos]] += pos;
        mth += count[a[pos]];
        val += 1LL * (r + 1) * count[a[pos]] - ld[a[pos]];
    };
    auto add = [&](int pos) {
        ++count[a[pos]];
        ld[a[pos]] += pos;
        mth += count[a[pos]];
        val += mth;
    };
    auto del = [&](int pos) {
        val -= mth;
        ld[a[pos]] -= pos;
        mth -= count[a[pos]];
        --count[a[pos]];
    };
    for (int i = 0, l = 0, r = 0; i < block.size(); ++i) {
        if (block[i].empty())
            continue;
        std::sort(block[i].begin(), block[i].end(), [&q](int lhs, int rhs) {
            return q[lhs].l > q[rhs].l;
        });
        for (int j = l; j <= r; ++j)
            count[a[j]] = ld[a[j]] = 0;
        val = 0;
        mth = 0;
        l = std::min(n, (i + 1) * BSZ + 1);
        r = std::min(n - 1, (i + 1) * BSZ);
        for (auto idx : block[i]) {
            auto [ql, qr] = q[idx];
            for (; l > ql;)
                addl(--l, r);
            for (; r < qr;)
                add(++r);
            for (; r > qr;)
                del(r--);
            ans[idx] = len[r - l] - val;
        }
    }
    for (int i = 0; i < q_; ++i) {
        cout << ans[i] << '\n';
    }
}

int main()
{
#ifndef __APPLE__
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
#else
    std::freopen("/Users/dmitrii/xcode_solution/xcode_solution/input.txt", "r", stdin);
    std::freopen("/Users/dmitrii/xcode_solution/xcode_solution/output.txt", "w", stdout);
#endif
    solve();
    return 0;
}
