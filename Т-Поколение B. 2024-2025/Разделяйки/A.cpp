#include <bits/stdc++.h>
using std::cin, std::cout, std::vector, std::pair;

#define sq(x) ((x) * (x))
using i64 = long long;
const i64 inf = 1e9;

struct pnt {
    i64 x, y;
};

bool cmpx(pnt const &lhs, pnt const &rhs) {
    if (lhs.x == rhs.x)
        return lhs.y < rhs.y;
    return lhs.x < rhs.x;
}
bool cmpy(pnt const &lhs, pnt const &rhs) {
    if (lhs.y == rhs.y)
        return lhs.x < rhs.x;
    return lhs.y < rhs.y;
}

using pp = pair<pnt, pnt>;
inline i64 dist(pp const &p) {
    auto [f, s] = p;
    i64 d = sq(f.x - s.x) + sq(f.y - s.y);
    return d;
}


bool operator<(pp const &lhs, pp const &rhs) {
    return dist(lhs) < dist(rhs);
};

int main() {
    cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
#ifdef __APPLE__
    std::freopen(std::getenv("FINPATH"), "r", stdin);
    std::freopen(std::getenv("FOUTPATH"), "w", stdout);
#endif
    int n;
    cin >> n;
    vector<pnt> dot(n);
    for (auto&& [x, y] : dot)
        cin >> x >> y;
    vector<pnt> tmp(n);
    vector<pnt> doty(n);
    std::sort(dot.begin(), dot.end(), cmpx);
    std::function<pp(int, int)> rec = [&](int l, int r) {
        pp rs{{inf, inf}, {-inf, -inf}};
        if (r - l <= 4) {
            for (int i = l; i < r; ++i) {
                doty[i] = dot[i];
                for (int j = i + 1; j < r; ++j) {
                    rs = std::min(rs, {dot[i], dot[j]});
                }
            }
            std::sort(doty.begin() + l, doty.begin() + r, cmpy);
            return rs;
        }
        int m = (l + r) >> 1;
        rs = std::min(rec(l, m), rec(m, r));
        i64 d = dist(rs);
        i64 mx = dot[m].x;
        for (int i = l, j = m; i < m; ++i) {
            if (sq(doty[i].x - mx) < d) {
                while (j + 1 < r && doty[j].y < doty[i].y && sq(doty[j].y - doty[i].y) > d)
                    ++j;
                while (j > m && doty[j].y > doty[i].y && sq(doty[j].y - doty[i].y) > d)
                    --j;
                for (int k = 0; k < 4 && j + k < r; ++k) {
                    rs = std::min(rs, {doty[i], doty[j + k]});
                }
            }
        }
        std::merge(doty.begin() + l, doty.begin() + m, doty.begin() + m, doty.begin() + r, tmp.begin(), cmpy);
        std::copy(tmp.begin(), tmp.begin() + r - l, doty.begin() + l);
        return rs;
    };
    auto [f, s] = rec(0, n);
    cout << f.x << " " << f.y << "\n" << s.x << " " << s.y << "\n";
    return 0;
}

