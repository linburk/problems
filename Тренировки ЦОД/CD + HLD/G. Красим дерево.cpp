#include <bits/stdc++.h>
#include <climits>

#define LOCAL__ 1 && __APPLE__
#define REDIRECT__ 1 && __APPLE__
#define PRECALCULATE__ 0
#define MULTITEST__ 0

/* clang-format off */
#define all(cont) cont.begin(), cont.end()
using std::string;
#if REDIRECT__
std::ifstream cin; std::ofstream cout;
#else
using std::cin, std::cout;
#endif
/* aliases */
using i8 = std::int8_t; using i16 = std::int16_t; using i32 = std::int32_t; using i64 = std::int64_t;
using u8 = std::uint8_t; using u16 = std::uint16_t; using u32 = std::uint32_t; using u64 = std::uint64_t; using f64 = long double; using f32 = float;
using pi32 = std::pair<i32, i32>; using vpi32 = std::vector<pi32>; using vvpi32 = std::vector<vpi32>; using pi64 = std::pair<i64, i64>; using vpi64 = std::vector<pi64>; using vvpi64 = std::vector<vpi64>; using pu32 = std::pair<u32, u32>; using pu64 = std::pair<u64, u64>;
using vi32 = std::vector<i32>; using vvi32 = std::vector<vi32>; using vi64 = std::vector<i64>; using vvi64 = std::vector<vi64>; using vu64 = std::vector<u64>; using vvu64 = std::vector<vu64>;
using vb = std::vector<bool>; using vvb = std::vector<vb>; using vc = std::vector<char>; using vvc = std::vector<vc>;
using si32 = std::set<i32>; using spi32 = std::set<pi32>; using si64 = std::set<i64>; using spi64 = std::set<pi64>;
using mpi32 = std::map<i32, i32>; using umpi32 = std::unordered_map<i32, i32>; using mpi64 = std::map<i64, i64>; using umpi64 = std::unordered_map<i64, i64>;
#if __GNUC__ && ( __x86_64__ || __arm64__ )
using i128 = __int128; using u128 = unsigned __int128;
using pi128 = std::pair<i128, i128>; using vpi128 = std::vector<pi128>; using vvpi128 = std::vector<vpi128>;
using vi128 = std::vector<i128>; using vvi128 = std::vector<vi128>;
using si128 = std::set<i128>; using spi128 = std::set<pi128>;
using mpi128 = std::map<i128, i128>; using umpi128 = std::unordered_map<i128, i128>;
#endif
template <typename T> using v = std::vector<T>;
template <typename T> using s = std::set<T>;
template <typename T, typename V> using p = std::pair<T, V>;
template <typename T, typename V> using m = std::map<T, V>;
template <typename T, typename V> using um = std::unordered_map<T, V>;
template <int N, typename T> struct tensor : public std::vector<tensor<N-1, T> > {
    template <typename ...Args> tensor(int n = 0, Args... args) : std::vector<tensor<N-1, T> >(n, tensor<N-1, T>(args...)) {}
};
template <typename T> struct tensor<1, T> : public std::vector<T> {
    tensor(int n = 0, T const& val = T()) : std::vector<T>(n, val) {}
};
/* in/out op. overloadings */
#if __GNUC__ && (__x86_64__ || __arm64__)
std::istream &operator>>(std::istream &is, i128 &rhs) {
    std::string in;
    cin >> in;
    i128 p = 1;
    rhs = 0;
    for (i64 i = in.size() - 1; i >= 0; --i, p *= 10) {
        rhs += p * (in[i] - '0');
    }
    return is;
}
std::ostream &operator<<(std::ostream &os, i128 const &rhs){
    std::string res;
    for (i128 tmp = (rhs < 0 ? -rhs : rhs); tmp; tmp /= 10)
        res += '0' + tmp % 10;
    if (rhs < 0) res += '-';
    if (rhs == 0) res += '0';
    for (auto i = res.rbegin(); i != res.rend(); ++i)
        os << *i;
    return os;
}
#endif
template <typename T, typename V> std::istream &operator>>(std::istream &is, std::pair<T, V> &p) { is >> p.first >> p.second; return is; }
template <typename T> std::istream &operator>>(std::istream &is, std::vector<T> &cont) { for (auto &i : cont) { is >> i; } return is; }
template <typename T, typename V, char SEP = ' ', char ENDL = '\n'> std::ostream &operator<<(std::ostream &os, std::pair<T, V> const &p) {
#if LOCAL__
    os << "<" << p.first << ", " << p.second << ">";
    return os;
#else
    os << p.first << SEP << p.second << ENDL;
    return os;
#endif
}
template <typename T, char SEP = ' ', char ENDL = '\n'> std::ostream &operator<<(std::ostream &os, const std::vector<T> &cont) {
#if LOCAL__
    os << "[";
    for (auto b = cont.begin(), e = cont.end(); b != e; ++b)
        os << *b << (b + 1 == e ? "" : ", "); os << "]";
    return os;
#else
    for (auto b = cont.begin(), e = cont.end(); b != e; ++b)
        os << *b << (b + 1 == e ? ENDL : SEP);
    return os;
#endif
}
/* functions */
#if __cplusplus >= 202002L
void print(auto &&...args) { ((cout << args), ...); }
void input(auto &&...args) { ((cin >> args), ...); }
#endif
template <typename T> void inline unique(std::vector<T> &cont) { cont.erase(std::unique(cont.begin(), cont.end()), cont.end()); }
std::mt19937_64 ru64(std::chrono::steady_clock().now().time_since_epoch().count());
/* clang-format on */

struct st {
	vvpi32 st;
	pi32 mx(pi32 &a, pi32 &b)
	{
		return a.second < b.second ? a : b;
	}
	void build(vpi32 &a)
	{
		st.resize(32 - __builtin_clz(a.size() + 1), vpi32(a.size()));
		st[0] = a;
		for (i32 i = 0; i + 1 < 32 - __builtin_clz(a.size() + 1); i++) {
			for (i32 j = 0; j < a.size() - (1 << i); j++) {
				st[i + 1][j] = mx(st[i][j], st[i][j + (1 << i)]);
			}
		}
	}
	i32 get(i32 l, i32 r)
	{
		i32 d = 31 - __builtin_clz(r - l);
		return mx(st[d][l], st[d][r - (1 << d)]).first;
	}
};
struct lca {
	vpi32 tour;
	vi32 in, out;
	st rmq;
	void dfs(vvpi32 &gr, i32 v, i32 p, i32 d)
	{
		in[v] = tour.size();
		tour.push_back({ v, d });
		for (auto [to, w] : gr[v]) {
			if (to != p) {
				dfs(gr, to, v, d + 1);
				tour.push_back({ v, d });
			}
		}
		out[v] = tour.size();
	}
	void build(vvpi32 &gr)
	{
		in.resize(gr.size());
		out.resize(gr.size());
		dfs(gr, 0, 0, 0);
		rmq.build(tour);
	}
	i32 get(i32 u, i32 v)
	{
		return rmq.get(std::min(in[u], in[v]), std::max(out[u], out[v]));
	}
};

struct dt {
	i32 len, c, t;
};

bool operator<(dt const &lhs, dt const &rhs)
{
	return lhs.len < rhs.len;
}

struct {
	i32 n;
	vi32 d;
	vvpi32 gr;
	vvi32 p;
	vb used;
	i32 t = 0;
	v<v<dt> > data;
	lca g;
	auto inline dist(i32 a, i32 b) -> i32
	{
		return d[a] + d[b] - 2 * d[g.get(a, b)];
	};
	void dfs1(i32 v, i32 p, i32 w)
	{
		d[v] = d[p] + w;
		for (auto [to, w] : gr[v]) {
			if (to != p)
				dfs1(to, v, w);
		}
	}
	i32 dfs2(i32 v, i32 p, i32 asz, i32 &c)
	{
		i32 sz = 1;
		for (auto [to, w] : gr[v]) {
			if (to != p && !used[to]) {
				sz += dfs2(to, v, asz, c);
			}
		}
		if (c == -1 && 2 * sz >= asz)
			c = v;
		return sz;
	}
	void build(i32 v, i32 pr)
	{
		i32 c = -1;
		i32 asz = dfs2(v, v, 0, c);
		c = -1;
		dfs2(v, v, asz, c);
		if (pr != -1)
			p[c] = p[pr];
		p[c].push_back(c);
		used[c] = 1;
		for (auto [to, w] : gr[c]) {
			if (!used[to]) {
				build(to, c);
			}
		}
	}
	void upd(i32 v, i32 c, i32 d)
	{
		for (i32 i = 0; i < p[v].size(); ++i) {
			i32 u = p[v][i];
			i32 len = d - dist(u, v);
			if (len < 0)
				continue;
			for (; data[u].size() && data[u].back().len <= len;
				 data[u].pop_back())
				;
			data[u].push_back({ len, c, t });
		}
		++t;
	}
	auto get(i32 v) -> i32
	{
		i32 rs = 0;
		i32 t = -1;
		for (i32 i = 0; i < p[v].size(); ++i) {
			i32 u = p[v][i];
			i32 len = dist(u, v);
			if (data[u].empty() || data[u][0].len < len || data[u].back().t < t)
				continue;
			auto q = std::lower_bound(data[u].rbegin(), data[u].rend(),
									  dt{ len, 0, 0 });
			if (q != data[u].rend()) {
				auto [_, c, tc] = *q;
				if (tc > t) {
					t = tc;
					rs = c;
				}
			}
		}
		return rs;
	}
	void solve()
	{
		cin >> n;
		gr.resize(n);
		for (i32 i = 1; i < n; ++i) {
			i32 u, v, w;
			cin >> u >> v >> w;
			--u, --v;
			gr[u].push_back({ v, w });
			gr[v].push_back({ u, w });
		}
		g.build(gr);
		d.resize(n);
		p.resize(n);
		used.resize(n);
		data.resize(n);
		dfs1(0, 0, 0);
		build(0, -1);
		i32 q;
		cin >> q;
		for (i32 i = 0; i < q; ++i) {
			char t;
			cin >> t;
			i32 v, d, c;
			if (t == '1') {
				cin >> v >> d >> c;
				--v;
				upd(v, c, d);
			} else {
				cin >> v;
				--v;
				cout << get(v) << '\n';
			}
		}
	}
	void precalculate();
} solution;

i32 main(i32 argc, char *argv[], char *envp[]) /* clang-format off */ {
    cin.tie(nullptr); std::ios_base::sync_with_stdio(false);
    std::setlocale(LC_ALL, "Russian");
#if REDIRECT__
    cin.open("/Users/dmitrii/xcode_solution/xcode_solution/input.txt");
    cout.open("/Users/dmitrii/xcode_solution/xcode_solution/output.txt");
#endif
#if PRECALCULATE__
    solution.precalculate();
#endif
#if MULTITEST__
    i32 t; cin >> t; for (i32 i = 0; i < t; i++)
#endif
        solution.solve();
#if REDIRECT__
    cin.close();
    cout.close();
#endif
    return 0;
} /* clang-format on */
