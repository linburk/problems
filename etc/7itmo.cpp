#include <iostream>
#include <vector>
#include <string>

using i32 = int;
using std::cin, std::cout, std::vector, std::string;

i32 const card_c = 12;
i32 const rev_c = 10;
i32 const plus_c = 11;
i32 const mult_c = 48;

i32 get_cd() {
    string s;
    cin >> s;
    if (s[0] == '*')
        return mult_c;
    i32 t = 0;
    if (s[0] == 'R') {
        t = 0 * card_c;
    } else if (s[0] == 'G') {
        t = 1 * card_c;
    } else if (s[0] == 'B') {
        t = 2 * card_c;
    } else if (s[0] == 'Y') {
        t = 3 * card_c;
    }
    if (s[1] == '@') {
        t += rev_c;
    } else if (s[1] == '+') {
        t += plus_c;
    } else {
        t += s[1] - '0';
    }
    return t;
}

void solve() {
    i32 n, a, q;
    cin >> n >> a >> q;
    i32 last = get_cd();
    vector<string> msg = {
        "missing card", // 0
        "wrong turn order", // 1
        "wrong action", // 2
        "card doesn't match", // 3
        "fail 'Uno!'" // 4
    };
    vector<vector<i32> > cd(n, vector<i32>(a));
    for (i32 i = 0; i < n; ++i) {
        for (i32 j = 0; j < a; ++j) {
            cd[i][j] = get_cd();
        }
    }
    vector<bool> used(n);
    i32 plus = 0;
    i32 mult = 0;
    i32 rev = 1;
    i32 cur = -1;
    i32 fl = 0;
    auto next = [&] (i32 c) -> i32 {
        auto step = [&] (i32 i) -> i32 {
            return (i + (rev ? 1 : -1) + n) % n;
        };
        for (i32 j = 0, i = step(c); j <= 2 * n; i = step(i), ++j) {
            if (!used[i])
                return i;
        }
        return cur;
    };
    auto print_msg = [&] (i32 t, i32 idx, i32 i) {
        cout << msg[t] << ", player " << idx << ", turn " << i;
        fl = 1;
    };
    for (i32 i = 0; i < q; ++i) {
        i32 idx;
        string act;
        cin >> idx >> act;
        --idx;
        bool his_turn = (next(cur) == idx);
        bool uno = 0;
        if (act == "says") {
            cin >> act >> act >> act >> act;
            uno = 1;
        }
        if (act == "plays") {
            i32 t = get_cd();
            if (!fl) {
                bool c = 0;
                for (i32 j = 0; j < cd[idx].size(); ++j) {
                    if (cd[idx][j] == t) {
                        c = 1;
                        cd[idx].erase(cd[idx].begin() + j);
                        break;
                    }
                }
                if (!c) {
                    print_msg(0, idx + 1, i + 1);
                    continue;
                }
                if (last != t && !his_turn) {
                    print_msg(1, idx + 1, i + 1);
                    continue;
                }
                if (cd[idx].size() == 0) {
                    used[idx] = 1;
                }
                if (((mult && t != mult_c) || (plus && t % card_c != plus_c))) {
                    print_msg(2, idx + 1, i + 1);
                    continue;
                }
                if (t != mult_c && last != mult_c && ((last % card_c != t % card_c && last / card_c != t / card_c))) {
                    print_msg(3, idx + 1, i + 1);
                    continue;
                }
                if (t == mult_c) {
                    if (!his_turn)
                        mult = 0;
                    ++mult;
                } else if (t % card_c == rev_c) {
                    rev ^= 1;
                } else if (t % card_c == plus_c) {
                    if (!his_turn)
                        plus = 0;
                    ++plus;
                }
                last = t;
            }
        } else {
            i32 k;
            cin >> k;
            if (!fl) {
                if (!his_turn || used[idx]) {
                    print_msg(1, idx + 1, i + 1);
                } else if ((plus != 0 && k != 2 * plus) || (mult != 0 && k != 4 * mult) || (mult == 0 && plus == 0 && k > 1) || k == 0) {
                    print_msg(2, idx + 1, i + 1);
                }
            }
            plus = 0;
            mult = 0;
            for (i32 j = 0; j < k; ++j) {
                i32 t = get_cd();
                if (!fl) {
                    cd[idx].push_back(t);
                }
            }
        }
        if (!fl && ((uno && cd[idx].size() != 1) || (!uno && cd[idx].size() == 1))) {
            print_msg(4, idx + 1, i + 1);
        }
        cur = idx;
    }
    if (!fl)
        cout << "ok";
}

i32 main() {
#ifdef __APPLE__
    std::freopen("/Users/dmitrii/xcode_solution/xcode_solution/input.txt", "r", stdin);
    std::freopen("/Users/dmitrii/xcode_solution/xcode_solution/output.txt", "w", stdout);
#endif
    i32 t;
    cin >> t;
    for (i32 i = 0; i < t; ++i) {
        solve();
        if (i != t - 1)
            cout << "\n";
    }
}

