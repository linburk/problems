#include <bits/stdc++.h>

#include <climits>
using namespace std;

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<vi> vvi;
typedef vector<vl> vvl;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef vector<vvi> vvvi;
typedef vector<vvl> vvvl;

#define all(cont) cont.begin(), cont.end()
#define funique(cont) cont.erase(unique(all(cont)), cont.end())

namespace tools
{
// mt19937_64 rng(chrono::steady_clock().now().time_since_epoch().count());
template <typename T>
std::istream &operator>>(std::istream &is, std::vector<T> &array)
{
	for (auto &i : array) {
		is >> i;
	}
	return is;
}
template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &array)
{
	for (const auto &i : array) {
		os << i << " ";
	}
	//        os << "\n";
	return os;
}
template <typename T, typename V>
std::istream &operator>>(std::istream &is, std::pair<T, V> &p)
{
	is >> p.first >> p.second;
	return is;
}
} // namespace tools

using namespace tools;

template <typename T> struct point {
	T x, y;

	point()
	{
	}

	point(int null)
		: x(0)
		, y(0)
	{
	}

	point(const T x, const T y)
		: x(x)
		, y(y)
	{
	}

	long double length()
	{
		return std::hypot(x, y);
	}

	long double radangle()
	{
		return std::atan2(y, x);
	}

	const point operator-()
	{
		return point(-(this->x), -(this->y));
	}

	point &operator+=(const point &A)
	{
		x += A.x, y += A.y;
		return *this;
	}

	point &operator-=(const point &A)
	{
		x -= A.x, y -= A.y;
		return *this;
	}

	point &operator*=(const long double q)
	{
		x *= q, y *= q;
		return *this;
	}

	const point operator+(const point &A) const
	{
		return point(*this) += A;
	}

	const point operator-(const point &A) const
	{
		return point(*this) -= A;
	}

	const point operator*(long double q) const
	{
		return point(*this) *= q;
	}

	const bool operator==(const point &A) const
	{
		return (A.x == (this->x) && A.y == (this->y));
	}

	const bool operator!=(const point &A) const
	{
		return !(A == *this);
	}

	const T operator*(const point &A) const
	{
		return (this->x) * A.x + (this->y) * A.y;
	}

	const T operator%(const point &A) const
	{
		return (this->x) * A.y - (this->y) * A.x;
	}
};

template <typename T> std::istream &operator>>(std::istream &is, point<T> &A)
{
	is >> A.x >> A.y;
	return is;
}

template <typename T> long double radangle(const point<T> &A, const point<T> &B)
{
	return atan2(A % B, A * B);
}

template <typename T> long double length(point<T> &A, point<T> &B)
{
	return std::hypot((A.x - B.x), (A.y - B.y));
}

template <typename T> long double area(std::vector<point<T> > &shape)
{
	long long S = 0;
	for (size_t i = 0; i < shape.size(); i++) {
		S += shape[i ? i - 1 : shape.size() - 1] % shape[i];
	}
	return (long double)std::abs(S) / 2;
}

template <typename T> struct vec {
	point<T> A, B;

	vec()
	{
	}

	vec(const point<T> &B)
		: A(0)
		, B(B)
	{
	}

	vec(const point<T> &A, const point<T> &B)
		: A(A)
		, B(B)
	{
	}

	long double length()
	{
		return length(A, B);
	}

	long double radangle()
	{
		return radangle(A, B);
	}

	void rotate(const long double angle)
	{
		long double newX, newY;
		B -= A;
		newX = B.x * cos(angle) - B.y * sin(angle);
		newY = B.x * sin(angle) + B.y * cos(angle);
		B.x = newX;
		B.y = newY;
		B += A;
	}

	vec &operator+=(const point<T> &C)
	{
		A += C;
		B += C;
		return *this;
	}

	vec &operator+=(const vec<T> &C)
	{
		point<T> BT = B - A, CT = C.B - C.A;
		B = BT + CT + A;
		return *this;
	}

	vec &operator-=(const point<T> &C)
	{
		A -= C, B -= C;
		return *this;
	}
	vec &operator-=(const vec<T> &C)
	{
		point<T> BT = B - A, CT = C.B - C.A;
		B = BT - CT + A;
		return *this;
	}

	vec &operator*=(const long double q)
	{
		B -= A;
		B *= q;
		B += A;
		return *this;
	}

	const vec operator-()
	{
		return vec(*this) *= -1;
	}

	const vec operator+(const point<T> &C) const
	{
		return vec(*this) += C;
	}

	const vec operator+(const vec &C) const
	{
		return vec(*this) += C;
	}

	const vec operator-(const point<T> &C) const
	{
		return vec(*this) -= C;
	}

	const vec operator-(const vec &C) const
	{
		return vec(*this) -= C;
	}

	const vec operator*(long double q) const
	{
		return vec(*this) *= q;
	}

	const bool operator==(const vec &C) const
	{
		const point AT = B - A;
		const point BT = C.B - C.A;
		return AT == BT;
	}

	const bool operator!=(const vec &C) const
	{
		return !(C == *this);
	}

	const T operator*(const vec &C)
	{
		const point AT = B - A;
		const point BT = C.B - C.A;
		return AT * BT;
	}

	const T operator%(const vec &C)
	{
		const point AT = B - A;
		const point BT = C.B - C.A;
		return AT % BT;
	}
};

template <typename T> long double radangle(vec<T> &A, vec<T> &B)
{
	const point AT = A.B - A.A;
	const point BT = B.B - B.A;
	return radangle(AT, BT);
}

void solve()
{
	int n;
	cin >> n;
	vector<point<ll> > shape(n);
	cin >> shape;
	cout << area(shape);
}

int32_t main()
{
	setlocale(LC_ALL, "Russian");
#ifdef __APPLE__
	std::freopen("/Users/dmitrii/Documents/Code/Code/input.txt", "r", stdin);
	std::freopen("/Users/dmitrii/Documents/Code/Code/output.txt", "w", stdout);
#endif
	std::cin.tie(0);
	std::ios_base::sync_with_stdio(false);
	//    int t;
	//    cin >> t;
	//    for (; t; t--)
	solve();
	return 0;
}
