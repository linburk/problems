#include <stdio.h>

#include <algorithm>
#include <bitset>
#include <cmath>
#include <deque>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>

#ifdef __APPLE__
#include <fstream>
std::ifstream input("input.txt");
std::ofstream output("output.txt");
#define cin input
#define cout output
#endif

using namespace std;

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

#define endl '\n'
#define all(cont) cont.begin(), cont.end()
#define pb(x) emplace_back(x)
#define $FASTSTREAM \
  std::cin.tie(0);  \
  std::cout.tie(0); \
  std::ios_base::sync_with_stdio(false);

namespace tools {

    template <typename T>
    T gcd(T a, T b) {
        while (b > 0) {
            a %= b;
            std::swap(a, b);
        }
        return a;
    }

    template <typename T>
    T lcm(T a, T b) {
        return a * b / gcd(a, b);
    }

    template <typename T>
    std::istream &operator>>(std::istream &is, std::vector<T> &array) {
        for (auto &i : array) {
            is >> i;
        }
        return is;
    }

    template <typename T>
    std::ostream &operator<<(std::ostream &os, const std::vector<T> &array) {
        for (const auto &i : array) {
            os << i << " ";
        }
        return os;
    }

    template <typename T>
    std::istream &operator>>(std::istream &is,
                             std::vector<std::vector<T> > &matrix) {
        for (auto &i : matrix)
            for (auto &j : i) is >> j;
        return is;
    }

    template <typename T>
    std::ostream &operator<<(std::ostream &os,
                             const std::vector<std::vector<T> > &matrix) {
        for (const auto &i : matrix) {
            for (const auto &j : i) os << j << " ";
            os << "\n";
        }
        return os;
    }

    template <typename T>
    std::istream &operator>>(std::istream &is, std::pair<T, T> &p) {
        is >> p.first >> p.second;
        return is;
    }

}  // namespace tools
using namespace tools;
namespace vectors {

    template<typename T>
    struct point {

        T x, y;

        point() {};

        point(int null): x(0), y(0) {}

        point(const T x, const T y) : x(x), y(y) {}

        long double length() {
            return std::hypot(x, y);
        }

        long double radangle() {
            return std::atan2(y, x);
        }

        const point operator-() { return point(-(this->x), -(this->y)); }

        point &operator+=(const point &A) {
            x += A.x, y += A.y;
            return *this;
        }

        point &operator-=(const point &A) {
            x -= A.x, y -= A.y;
            return *this;
        }

        point &operator*=(const long double q) {
            x *= q, y *= q;
            return *this;
        }

        const point operator+(const point &A) const { return point(*this) += A; }

        const point operator-(const point &A) const { return point(*this) -= A; }

        const point operator*(long double q) const { return point(*this) *= q; }

        const bool operator==(const point &A) const { return (A.x == (this->x) and A.y == (this->y)); }

        const bool operator!=(const point &A) const { return !(A == *this); }

        const T operator*(const point &A) const { return (this->x) * A.x + (this->y) * A.y; }

        const T operator%(const point &A) const { return (this->x) * A.y - (this->y) * A.x; }



    };

    template<typename T>
    std::istream &operator>>(std::istream &is, point<T> &A) {
        is >> A.x >> A.y;
        return is;
    }

    template<typename T>
    long double radangle(const point<T> &A, const point<T> &B) {
        return atan2(A % B, A * B);
    }

    template<typename T>
    long double length(point<T> &A, point<T> &B) {
        return std::hypot((A.x - B.x), (A.y - B.y));
    }

    template<typename T>
    long double area(std::vector<point<T>> shape) {
        long double S = shape[size(shape) - 1] % shape[0];
        for (size_t i = 0; i < size(shape) - 1; i++) {
            S += shape[i] % shape[i + 1];
        }
        S /= -2;
        return std::abs(S);
    }

    template<typename T>
    struct vec {
        point<T> A, B;

        vec(){};

        vec(const point<T> &B): A(0), B(B) {};

        vec(const point<T>& A, const point<T>& B): A(A), B(B) {};

        long double length() {
            return vectors::length(A, B);
        }

        long double radangle() {
            return vectors::radangle(A, B);
        }

        void rotate(const long double angle){
            long double newX, newY;
            B -= A;
            newX = B.x * cos(angle) - B.y * sin(angle);
            newY = B.x * sin(angle) + B.y * cos(angle);
            B.x = newX;
            B.y = newY;
            B += A;
        }

        vec &operator+=(const point<T> &C) {
            A += C; B += C;
            return *this;
        }

        vec &operator+=(const vec<T> &C) {
            point<T> BT = B - A, CT = C.B - C.A;
            B = BT + CT + A;
            return *this;
        }

        vec &operator-=(const point<T> &C) {
            A -= C, B -= C;
            return *this;
        }
        vec &operator-=(const vec<T> &C) {
            point<T> BT = B - A, CT = C.B - C.A;
            B = BT - CT + A;
            return *this;
        }

        vec &operator*=(const long double q) {
            B -= A;
            B *= q;
            B += A;
            return *this;
        }

        const vec operator-() { return vec(*this) *= -1; }

        const vec operator+(const point<T> &C) const { return vec(*this) += C; }

        const vec operator+(const vec &C) const { return vec(*this) += C; }

        const vec operator-(const point<T> &C) const { return vec(*this) -= C; }

        const vec operator-(const vec &C) const { return vec(*this) -= C; }

        const vec operator*(long double q) const { return vec(*this) *= q; }

        const bool operator==(const vec &C) const {
            const point AT = B - A;
            const point BT = C.B - C.A;
            return AT == BT;
        }

        const bool operator!=(const vec &C) const { return !(C == *this); }

        const T operator*(const vec &C) {
            const point AT = B - A;
            const point BT = C.B - C.A;
            return AT * BT;
        }

        const T operator%(const vec &C) {
            const point AT = B - A;
            const point BT = C.B - C.A;
            return AT % BT;
        }

    };

    template<typename T>
    long double radangle(vec<T> &A, vec<T> &B){
        const point AT = A.B - A.A;
        const point BT = B.B - B.A;
        return vectors::radangle(AT, BT);
    }
}
using namespace vectors;
void solve() {
    int a, b, c;
    point<ld> C;
    cin >> a >> b >> c >> C;
    point<ld> A(15, (ld)(-c - 15 * a) / b), B((ld)(-c - 10 * b) / a, 10);
    if (b == 0) {
        A.y = 2 * B.y;
        A.x = B.x;
    }
    if (a == 0) {
        B.y = A.y;
        B.x = 2 * A.x;
    }
    point<ld> N = point<ld>((B - A).y, -(B - A).x) + C;
    ld dist = abs(vec(A, B) % vec(A, C)) / vec(A, B).length() ;
    ld AK = N.y - C.y;
    ld BK = C.x - N.x;
    ld CK = -AK * N.x - BK * N.y;
    cout << setprecision(7) << fixed << AK << " " << BK << " " << CK;
}

int32_t main() {
    setlocale(LC_ALL, "Russian");
#ifndef __APPLE__
    $FASTSTREAM
#endif
//    int t;
//    cin >> t;
//    for (int i = 0; i < t; i++)
    solve();
    return 0;
}