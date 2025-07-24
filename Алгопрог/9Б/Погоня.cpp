#include <iostream>
#include <vector>
#include <deque>
#include <array>

using std::cin, std::cout, std::vector, std::string, std::deque;
using i16 = short int;
using vi16 = vector<i16>;
using vvi16 = vector<vi16>;
using vvvi16 = vector<vvi16>;
using vvvvi16 = vector<vvvi16>;
using vc = vector<char>;
using vvc = vector<vc>;
using vvvc = vector<vvc>;
using vvvvc = vector<vvvc>;

enum {
    draw = 0,
    win = 1,
    lose = 2,
};

struct state {
    int e, o, t, p;
    operator int() {
        return e * 10 * 300 * 300 + o * 300 * 300 + t * 300 + p;
    }
};

int n, m, k;
char dp[2 * 10 * 300 * 300] = {draw};
i16 d[2 * 10 * 300 * 300] = {0};
i16 dg[2 * 10 * 300 * 300] = {0};
vvvi16 gr;

int main() {
#ifdef __APPLE__
    std::freopen("/users/dmitrii/xcode_solution/xcode_solution/input.txt", "r", stdin);
    std::freopen("/users/dmitrii/xcode_solution/xcode_solution/output.txt", "w", stdout);
#endif
    cin >> n >> m >> k;
    ++k;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 300; ++j) {
            for (int k = 0; k < 300; ++k) {
                d[state{0, i, j, k}] = 0;
                d[state{1, i, j, k}] = 1E4;
            }
        }
    }
    gr.resize(k, vvi16(n));
    for (int i = 0; i < m; ++i) {
        int x, y, t;
        cin >> x >> y >> t;
        --x, --y;
        gr[t][x].push_back(y);
        gr[t][y].push_back(x);
    }
    deque<state> q;
    {
        state end = {1, 0, 0, 0};
        dp[end] = win;
        d[end] = 0;
        q.push_back(end);
        for (int j = 1; j < k; ++j) {
            end = {0, j, 0, 0};
            d[end] = 0;
            dp[end] = lose;
            q.push_back(end);
        }
    }
    for (int i = 1; i < n; ++i) {
        for (int j = 1; j < k; ++j) {
            state end = {0, j, i, i};
            d[end] = 0;
            dp[end] = lose;
            q.push_front(end);
        }
        state end = {1, 0, i, i};
        d[end] = 0;
        dp[end] = win;
        q.push_back(end);
    }
    for (int i = 1; i < n; ++i) {
        state end = {1, 0, 0, i};
        d[end] = 0;
        dp[end] = lose;
        q.push_front(end);
        for (int j = 1; j < k; ++j) {
            end = {0, j, 0, i};
            d[end] = 0;
            dp[end] = win;
            q.push_back(end);
        }
    }
    for (int t = 0; t < n; ++t) {
        for (int p = 0; p < n; ++p) {
            for (int no = 1; no < k; ++no) {
                state cur = {1, 0, t, p};
                dg[cur] += gr[no][p].size();
            }
        }
    }
    for (int o = 1; o < k; ++o) {
        for (int t = 0; t < n; ++t) {
            for (int p = 0; p < n; ++p) {
                state cur = {0, o, t, p};
                dg[cur] += gr[o][t].size() + 1;
            }
        }
    }
    for (; q.size();) {
        state cur = q.front();
        auto [e, o, t, p] = cur;
        q.pop_front();
        if (e == 0) {
            for (auto to : gr[o][p]) {
                state prev = {1, 0, t, to};
                if (!dp[prev]) {
                    if (dp[cur] == lose) {
                        dp[prev] = win;
                        q.push_back(prev);
                    } else if (--dg[prev] == 0) {
                        dp[prev] = lose;
                        q.push_front(prev);
                    } else continue;
                    d[prev] = std::min((int)d[prev], d[cur] + 1);
                }
            }
        }
        if (e == 1) {
            for (int no = 1; no < k; ++no) {
                for (auto to : gr[no][t]) {
                    state prev = {0, no, to, p};
                    if (!dp[prev]) {
                        if (dp[cur] == lose) {
                            dp[prev] = win;
                            q.push_back(prev);
                        } else if (--dg[prev] == 0) {
                            dp[prev] = lose;
                            q.push_front(prev);
                        } else continue;
                        d[prev] = std::max(d[prev], d[cur]);
                    }
                }
                state prev = {0, no, t, p};
                if (!dp[prev]) {
                    if (dp[cur] == lose) {
                        dp[prev] = win;
                        q.push_back(prev);
                    } else if (--dg[prev] == 0) {
                        dp[prev] = lose;
                        q.push_front(prev);
                    } else continue;
                    d[prev] = std::max(d[prev], d[cur]);
                }
            }
        }
    }
    int pp, tt;
    cin >> pp >> tt;
    --pp, --tt;
    state st = {1, 0, tt, pp};
    cout << (dp[st] ? dp[st] == win ? "Caught\n" : "Escaped\n" : "Endless\n");
    if (dp[st])
        cout << d[st] << "\n";
    return 0;
}