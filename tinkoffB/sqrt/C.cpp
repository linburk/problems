#include <cmath>
#include <iostream>
#include <vector>

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
    int n, m;
    std::cin >> n >> m;
    std::vector<std::pair<int, int>> a(n);
    std::vector<std::pair<int, int>> b(m);
    for (auto&& [a, b] : a) {
        std::cin >> a >> b;
        a = std::min(a, 200000);
    }
    for (auto&& [c, d] : b) {
        std::cin >> c >> d;
    }
    std::vector<int> ans(n);
    int const BSZ = 555;
    std::vector<i64> pref(2E5 + 2);
    std::vector<i64> dmg_val(2E5 + 2, 1E18);
    dmg_val[0] = 0;
    for (int i = 0; i < m; ++i) {
        std::vector<std::pair<int, int>> jmp;
        int hp = b[i].second;
        int hb = std::ceil(std::sqrt(hp));
        int r = 1;
        hb *= hb;
        for (int j = 1; j * j <= hb; ++j) {
            jmp.push_back({ j, (hp + j - 1) / j });
            r = j;
        }
        for (int j = jmp.size() - 1; j >= 0; --j) {
            if (jmp[j].second > r) {
                if ((hp + jmp[j].second - 1) / jmp[j].second == jmp[j].first) {
                    jmp.push_back({ jmp[j].second, jmp[j].first });
                    r = jmp[j].second;
                }
            }
        }
        jmp.push_back({ 2E5 + 1, 0 });
        for (int j = 0; j < jmp.size() - 1; ++j) {
            i64 val = 1LL * jmp[j].second * b[i].first;
            pref[jmp[j].first] += val;
            pref[jmp[j + 1].first] -= val;
        }
        if ((i + 1) % BSZ == 0) {
            for (int j = 1; j < 2E5 + 2; ++j) {
                dmg_val[j] = dmg_val[j - 1] + pref[j];
                pref[j] = 0;
            }
            for (int j = 0; j < n; ++j) {
                if (ans[j] != i / BSZ * BSZ)
                    continue;
                int dmg = a[j].first;
                int hp = a[j].second;
                if (hp > dmg_val[dmg]) {
                    a[j].second -= dmg_val[dmg];
                    ans[j] += BSZ;
                }
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        int dmg = a[i].first;
        int hp = a[i].second;
        for (; ans[i] < m;) {
            int dmg2 = b[ans[i]].first;
            int hp2 = b[ans[i]].second;
            i64 dmg_rec = 1LL * (hp2 + dmg - 1) / dmg * dmg2;
            if (hp - dmg_rec > 0) {
                ++ans[i];
                hp -= dmg_rec;
            } else {
                if (hp - dmg_rec + dmg2 > 0)
                    ++ans[i];
                break;
            }
        }
        std::cout << ans[i] << '\n';
    }
    return 0;
}