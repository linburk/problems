#include <climits>
#include <cmath>
#include <iostream>
#include <vector>

struct sr_d {
    struct block {
        std::vector<int> el;
        int min = INT_MAX;
    };
    int op_cnt = 0;
    int sz = 0;
    int const OP_SZ = 700;
    std::vector<block> blocks = { block {} };
    int min(int l, int r)
    {
        int res = INT_MAX;
        int c = 0;
        int i = 0;
        for (; i < blocks.size();) {
            int c_sz = blocks[i].el.size();
            if (c + c_sz < l) {
                c += c_sz;
                ++i;
            } else {
                break;
            }
        }
        for (int j = 0; c < r && j < blocks[i].el.size(); ++j, ++c) {
            if (c >= l) {
                res = std::min(res, blocks[i].el[j]);
            }
        }
        ++i;
        for (; i < blocks.size();) {
            int c_sz = blocks[i].el.size();
            if (c + c_sz < r) {
                res = std::min(res, blocks[i].min);
                c += c_sz;
                ++i;
            } else {
                break;
            }
        }
        for (int j = 0; c < r && j < blocks[i].el.size(); ++j, ++c) {
            if (c >= l) {
                res = std::min(res, blocks[i].el[j]);
            }
        }
        return res;
    }
    void add(int pos, int x)
    {
        if (op_cnt > OP_SZ) {
            rebuild();
        }
        int i = 0;
        for (; i < blocks.size();) {
            int c_sz = blocks[i].el.size();
            if (pos - c_sz > 0) {
                pos -= c_sz;
                ++i;
            } else {
                break;
            }
        }
        blocks[i].el.insert(blocks[i].el.begin() + pos, x);
        blocks[i].min = std::min(blocks[i].min, x);
        ++op_cnt;
        ++sz;
    }
    void rebuild()
    {
        int const BLOCK_SZ = std::sqrt(sz) + 1;
        int k = 0;
        int c = 0;
        std::vector<block> r_blocks(sz / BLOCK_SZ + 1);
        for (int i = 0; i < blocks.size(); ++i) {
            for (int j = 0; j < blocks[i].el.size(); ++j, ++c) {
                if (c == BLOCK_SZ) {
                    ++k;
                    c = 0;
                }
                r_blocks[k].el.push_back(blocks[i].el[j]);
                r_blocks[k].min = std::min(r_blocks[k].min, blocks[i].el[j]);
            }
        }
        blocks = std::move(r_blocks);
        op_cnt = 0;
    }
};

int main()
{
#ifdef __APPLE__
    std::freopen("input.txt", "r", stdin);
    std::freopen("output.txt", "w", stdout);
#else
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
#endif
    int n;
    std::cin >> n;
    sr_d d;
    for (int i = 0; i < n; ++i) {
        char c;
        std::cin >> c;
        if (c == '+') {
            int pos, x;
            std::cin >> pos >> x;
            d.add(pos, x);
        } else {
            int l, r;
            std::cin >> l >> r;
            std::cout << d.min(l - 1, r) << '\n';
        }
    }
    return 0;
}
