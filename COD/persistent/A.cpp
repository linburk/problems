#include <iostream>
#include <vector>
#include <ext/pb_ds/assoc_container.hpp>

using i64 = long long;

struct persistent_st {
  i64 constexpr static UB = 0x52525252;
private:
  struct node {
    int l_son = UB, r_son = UB;
    int val = UB;
    node() {}
    node(node const &n) { *this = n; }
  };
  std::vector<node> nd;
  std::vector<i64> rt;
  i64 size;
private:
  i64 update(i64 i, i64 val, i64 l, i64 r, i64 n) {
    nd.push_back(n == UB ? node() : node(nd[n]));
    n = nd.size() - 1;
    if (l == r - 1) {
      nd[n].val = val;
      return n;
    }
    i64 m = (l + r) >> 1;
    if (i < m)
      nd[n].l_son = update(i, val, l, m, nd[n].l_son);
    else
      nd[n].r_son = update(i, val, m, r, nd[n].r_son);
    nd[n].val = std::min(nd[n].l_son == UB ? UB : nd[nd[n].l_son].val, nd[n].r_son == UB ? UB : nd[nd[n].r_son].val);
    return n;
  }
  i64 get(i64 ql, i64 qr, i64 l, i64 r, i64 n) {
    if (l >= qr || r <= ql || n == UB)
      return UB;
    if (ql <= l && r <= qr)
      return nd[n].val;
    i64 m = (l + r) >> 1;
    return std::min(get(ql, qr, l, m, nd[n].l_son), get(ql, qr, m, r, nd[n].r_son));
  }
public:
  persistent_st(i64 size_) {
    size = size_;
    nd.reserve(8E6);
    rt.reserve(5E5);
    nd.resize(1);
    rt.push_back(0);
  }
  i64 update(i64 i, i64 val) {
    rt.push_back(update(i, val, 0, size, rt.back()));
    return rt.back();
  }
  i64 get(i64 ql, i64 qr, i64 version) {
    return get(ql, qr, 0, size, version);
  }
};

int main(int argc, char ** argv) {
  int n, m;
  std::cin >> n >> m;
  std::vector<i64> arr(n);
  for (auto &&i : arr)
    std::cin >> i;
  __gnu_pbds::gp_hash_table<i64, i64> match;
  persistent_st st(n);
  std::vector<i64> vers(n);
  for (auto &&i : arr)
    match[i] = -1;
  for (i64 i = n - 1; i >= 0; --i) {
    if (i + 1 < n)
      vers[i] = vers[i + 1];
    if (match[arr[i]] != -1)
      vers[i] = st.update(match[arr[i]], match[arr[i]] - i);
    match[arr[i]] = i;
  }
  for (i64 i = 0; i < m; ++i) {
    i64 ql, qr;
    std::cin >> ql >> qr; --ql;
    i64 res = st.get(ql, qr, vers[ql]);
    std::cout << (res == persistent_st::UB ? -1 : res) << '\n';
  }
}
