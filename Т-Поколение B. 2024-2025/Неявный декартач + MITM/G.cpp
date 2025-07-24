#include <algorithm>
#include <bitset>
#include <cassert>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using std::cin, std::cout, std::string;
using std::vector, std::pair, std::bitset;

using i64 = long long;

int main()
{
    cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
#ifdef __APPLE__
    std::freopen(std::getenv("FINPATH"), "r", stdin);
    std::freopen(std::getenv("FOUTPATH"), "w", stdout);
#endif

    vector<pair<int, char>> blocks;
    auto insert = [&](int l, int alen, char ac) {
        if (l == 0) {
            blocks.insert(blocks.begin(), { alen, ac });
            return;
        }
        for (int i = 0, j = 0; j < blocks.size(); ++j) {
            auto [len, c] = blocks[j];
            if (i + len == l) {
                blocks.insert(blocks.begin() + j + 1, { alen, ac });
                return;
            }
            if (i + len > l) {
                int right = i + len - l;
                blocks[j] = { l - i, c };
                blocks.insert(blocks.begin() + j + 1, { alen, ac });
                blocks.insert(blocks.begin() + j + 2, { right, c });
                return;
            }
            i += len;
        }
    };
    auto erase = [&](int l, int dlen) {
        for (int i = 0, j = 0; dlen && j < blocks.size(); ++j) {
            if (i >= l) {
                while (dlen) {
                    auto [len, c] = blocks[j];
                    int ers = std::min(dlen, len);
                    if (ers == len) {
                        blocks.erase(blocks.begin() + j);
                    } else {
                        blocks[j] = { len - ers, c };
                    }
                    dlen -= ers;
                }
            }
            auto [len, c] = blocks[j];
            if (i + len > l) {
                int ers = std::min(dlen, i + len - l);
                blocks[j] = { len - ers, c };
                dlen -= ers;
            }
            i += len;
        }
    };
    auto count = [&](int l, int r) {
        bitset<26> res;
        for (int i = 0, j = 0; i < r && j < blocks.size(); ++j) {
            auto [len, c] = blocks[j];
            if (i + len > l)
                res[c] = 1;
            i += len;
        }
        return res.count();
    };
    //    auto rebuild = [&] () {};
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        char c;
        cin >> c;
        if (c == '-') {
            int i, c;
            cin >> i >> c;
            erase(i - 1, c);
        } else if (c == '+') {
            int i, x;
            char c;
            cin >> i >> x >> c;
            c -= 'a';
            insert(i - 1, x, c);
        } else {
            int l, r;
            cin >> l >> r;
            cout << count(l - 1, r) << "\n";
        }
    }
}
