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

namespace geometry
{

template <typename T> struct point {
	T x, y;
	point();
	point(int null);
	point(const T x, const T y);
	long double length();
	long double radangle();
	const point operator-();
	point &operator+=(const point &pnt);
	point &operator-=(const point &pnt);
	point &operator*=(const long double q);
	const point operator+(const point &pnt) const;
	const point operator-(const point &pnt) const;
	const point operator*(long double q) const;
	const bool operator==(const point &pnt) const;
	const bool operator!=(const point &pnt) const;
	const T operator*(const point &pnt) const; // Scalar product
	const T operator%(const point &pnt) const; // Vector product
};

template <typename T> std::istream &operator>>(std::istream &is, point<T> &pnt);

template <typename T>
long double radangle(const point<T> &pntA, const point<T> &pntB);

template <typename T>
long double length(const point<T> &pntA, const point<T> &pntB);

template <typename T> long double area(const std::vector<point<T> > &shape);

template <typename T> struct mvector {
	point<T> st, end;
	mvector();
	mvector(const point<T> &end);
	mvector(const point<T> &st, const point<T> &end);
	long double length();
	long double radangle();
	void rotate(const long double angle);
	mvector &operator+=(const mvector &mvec);
	mvector &operator-=(const mvector &mvec);
	mvector &operator*=(const long double q);

	const mvector operator-() const;
	const mvector operator+(const mvector &mvec) const;
	const mvector operator-(const mvector &mvec) const;
	const mvector operator*(long double q) const;
	const bool operator==(const mvector &mvec) const;
	const bool operator!=(const mvector &mvec) const;
	const T operator*(const mvector &mvec);
	const T operator%(const mvector &mvec);
	mvector &operator+=(const point<T> &pnt);
	mvector &operator-=(const point<T> &pnt);
	const mvector operator+(const point<T> &pnt) const;
	const mvector operator-(const point<T> &pnt) const;
};

template <typename T>
long double radangle(mvector<T> &mvecA, mvector<T> &mvecB);

template <typename T> point<T>::point()
{
}

template <typename T>
point<T>::point(int null)
	: x(0)
	, y(0)
{
}

template <typename T>
point<T>::point(const T x, const T y)
	: x(x)
	, y(y)
{
}

template <typename T> long double point<T>::length()
{
	return std::hypot(x, y);
}

template <typename T> long double point<T>::radangle()
{
	return std::atan2(y, x);
}

template <typename T> const point<T> point<T>::operator-()
{
	return point(-(this->x), -(this->y));
}

template <typename T> point<T> &point<T>::operator+=(const point<T> &pnt)
{
	x += pnt.x, y += pnt.y;
	return *this;
}
template <typename T> point<T> &point<T>::operator-=(const point<T> &pnt)
{
	x -= pnt.x, y -= pnt.y;
	return *this;
}

template <typename T> point<T> &point<T>::operator*=(const long double q)
{
	x *= q, y *= q;
	return *this;
}

template <typename T> const point<T> point<T>::operator+(const point &pnt) const
{
	return point(*this) += pnt;
}
template <typename T> const point<T> point<T>::operator-(const point &pnt) const
{
	return point(*this) -= pnt;
}

template <typename T> const point<T> point<T>::operator*(long double q) const
{
	return point(*this) *= q;
}

template <typename T> const bool point<T>::operator==(const point &pnt) const
{
	return (pnt.x == (this->x) && pnt.y == (this->y));
}

template <typename T> const bool point<T>::operator!=(const point &pnt) const
{
	return !(pnt == *this);
}

template <typename T> const T point<T>::operator*(const point &pnt) const
{
	return (this->x) * pnt.x + (this->y) * pnt.y;
}

template <typename T> const T point<T>::operator%(const point &pnt) const
{
	return (this->x) * pnt.y - (this->y) * pnt.x;
}

template <typename T> std::istream &operator>>(std::istream &is, point<T> &A)
{
	is >> A.x >> A.y;
	return is;
}

template <typename T>
long double radangle(const point<T> &pntA, const point<T> &pntB)
{
	return atan2(pntA % pntB, pntA * pntB);
}

template <typename T> long double length(point<T> &pntA, point<T> &pntB)
{
	return std::hypot((pntA.x - pntB.x), (pntA.y - pntB.y));
}

template <typename T> long double area(const std::vector<point<T> > &shape)
{
	long long S = 0;
	for (size_t i = 0; i < shape.size(); i++) {
		S += shape[i] % shape[(i + 1) % shape.size()];
	}
	return (long double)std::abs(S) / 2;
}

template <typename T> mvector<T>::mvector()
{
}

template <typename T>
mvector<T>::mvector(const point<T> &pnt)
	: st(0)
	, end(pnt)
{
}

template <typename T>
mvector<T>::mvector(const point<T> &pntA, const point<T> &pntB)
	: st(pntA)
	, end(pntB)
{
}

template <typename T> long double mvector<T>::length()
{
	return length(st, end);
}

template <typename T> long double mvector<T>::radangle()
{
	return radangle(st, end);
}

template <typename T> void mvector<T>::rotate(const long double angle)
{
	long double newX, newY;
	end -= st;
	newX = end.x * cos(angle) - end.y * sin(angle);
	newY = end.x * sin(angle) + end.y * cos(angle);
	end.x = newX;
	end.y = newY;
	end += st;
}

template <typename T> mvector<T> &mvector<T>::operator+=(const point<T> &pnt)
{
	st += pnt;
	end += pnt;
	return *this;
}

template <typename T> mvector<T> &mvector<T>::operator+=(const mvector<T> &mvec)
{
	point<T> tEndSt = end - st, tMvecEndSt = mvec.end - mvec.st;
	end = tEndSt + tMvecEndSt + st;
	return *this;
}

template <typename T> mvector<T> &mvector<T>::operator-=(const point<T> &pnt)
{
	st -= pnt, end -= pnt;
	return *this;
}
template <typename T> mvector<T> &mvector<T>::operator-=(const mvector<T> &mvec)
{
	point<T> tEndSt = end - st, tMvecEndSt = mvec.end - mvec.st;
	end = tEndSt - tMvecEndSt + st;
	return *this;
}

template <typename T> mvector<T> &mvector<T>::operator*=(const long double q)
{
	end -= st;
	end *= q;
	end += st;
	return *this;
}

template <typename T> const mvector<T> mvector<T>::operator-() const
{
	return vec(*this) *= -1;
}

template <typename T>
const mvector<T> mvector<T>::operator+(const point<T> &pnt) const
{
	return mvector(*this) += pnt;
}

template <typename T>
const mvector<T> mvector<T>::operator+(const mvector<T> &mvec) const
{
	return mvector(*this) += mvec;
}

template <typename T>
const mvector<T> mvector<T>::operator-(const point<T> &pnt) const
{
	return mvector(*this) -= pnt;
}

template <typename T>
const mvector<T> mvector<T>::operator-(const mvector<T> &mvec) const
{
	return mvector(*this) -= mvec;
}

template <typename T>
const mvector<T> mvector<T>::operator*(long double q) const
{
	return mvector(*this) *= q;
}

template <typename T>
const bool mvector<T>::operator==(const mvector<T> &mvec) const
{
	const point tEndSt = end - st;
	const point tMvecStEnd = mvec.end - mvec.st;
	return tEndSt == tMvecStEnd;
}

template <typename T>
const bool mvector<T>::operator!=(const mvector<T> &mvec) const
{
	return !(mvec == (*this));
}

template <typename T> const T mvector<T>::operator*(const mvector<T> &mvec)
{
	const point tEndSt = end - st;
	const point tMvecEndSt = mvec.end - mvec.st;
	return tEndSt * tMvecEndSt;
}

template <typename T> const T mvector<T>::operator%(const mvector<T> &mvec)
{
	const point tEndSt = end - st;
	const point tMvecEndSt = mvec.end - mvec.st;
	return tEndSt % tMvecEndSt;
}

template <typename T> long double radangle(mvector<T> &mvecA, mvector<T> &mvecB)
{
	const point tEndStA = mvecA.end - mvecA.st;
	const point tEndStB = mvecB.end - mvecA.st;
	return radangle(tEndStA, tEndStB);
}

} // namespace geometry
using namespace geometry;

void solve()
{
	point<ll> A, B, C, D;
	cin >> A >> B >> C >> D;

	ld A1 = B.y - A.y, B1 = A.x - B.x, C1 = A1 * A.x + B1 * A.y,

	   A2 = D.y - C.y, B2 = C.x - D.x, C2 = A2 * C.x + B2 * C.y;

	ld determinant = A1 * B2 - B1 * A2;
	ld determinant_x = B2 * C1 - B1 * C2;
	ld determinant_y = A1 * C2 - C1 * A2;
	ld x = 0, y = 0;
	if (determinant != 0) {
		x = determinant_x / determinant;
		y = determinant_y / determinant;
	} else {
		if (determinant_x == 0 && determinant_y == 0) {
			cout << 2;
		} else {
			cout << 0;
		}
		return;
	}

	cout << 1 << setprecision(7) << fixed << " " << x << " " << y;
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
