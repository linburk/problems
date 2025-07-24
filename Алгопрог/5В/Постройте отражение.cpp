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

    struct point {
        long double x, y;

        point() {};

        point(int null): x(0), y(0) {}

        point(const long double x, const long double y) : x(x), y(y) {}

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

        const long long operator*(const point &A) const { return (this->x) * A.x + (this->y) * A.y; }

        const long long operator%(const point &A) const { return (this->x) * A.y - (this->y) * A.x; }



    };

    std::istream &operator>>(std::istream &is, point &A) {
        is >> A.x >> A.y;
        return is;
    }

    long double radangle(const point &A, const point &B) {
        return atan2(A % B, A * B);
    }

    long double length(point &A, point &B) {
        return std::hypot((A.x - B.x), (A.y - B.y));
    }

    long double area(std::vector<point> shape) {
        long double S = shape[size(shape) - 1] % shape[0];
        for (size_t i = 0; i < size(shape) - 1; i++) {
            S += shape[i] % shape[i + 1];
        }
        S /= -2;
        return std::abs(S);
    }

    struct vec {
        point A, B;

        vec(){};

        vec(const point &B): A(0), B(B) {};

        vec(const point& A, const point& B): A(A), B(B) {};

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
        const vec operator-() { return vec(-A, -B); }

        vec &operator+=(const point &C) {
            A += C; B += C;
            return *this;
        }

        vec &operator-=(const point &C) {
            A -= C, B -= C;
            return *this;
        }

        vec &operator*=(const long double q) {
            B -= A;
            B *= q;
            B += A;
            return *this;
        }

        const vec operator+(const point &C) const { return vec(*this) += C; }

        const vec operator-(const point &C) const { return vec(*this) -= C; }

        const vec operator*(long double q) const { return vec(*this) *= q; }

        const bool operator==(const vec &C) const {
            const point AT = B - A;
            const point BT = C.B - C.A;
            return AT == BT;
        }

        const bool operator!=(const vec &C) const { return !(C == *this); }

        const long long operator*(const vec &C) {
            const point AT = B - A;
            const point BT = C.B - C.A;
            return AT * BT;
        }

        const long long operator%(const vec &C) {
            const point AT = B - A;
            const point BT = C.B - C.A;
            return AT % BT;
        }

    };

    long double radangle(vec &A, vec &B){
        const point AT = A.B - A.A;
        const point BT = B.B - B.A;
        return vectors::radangle(AT, BT);
    }
}
using namespace vectors;
void solve() {
    int a, b, c;
    point C;
    cin >> a >> b >> c >> C;
    cout << setprecision(6) << fixed;
    ll t = 1, p = -1;
    point A(t, (ld)(-c - t * a) / b), B(p, (ld)(-c - p * a) / b);
    if (a == 0){
        ld Y = (ld)-c / b;
        C.y = -(C.y - Y) + Y;
        cout << C.x << " " << C.y;
        exit(0);
    }
    if (b == 0){
        ld X = (ld)-c / a;
        C.x = -(C.x - X) + X;
        cout << C.x << " " << C.y;
        exit(0);
    }
    point T = A - B;
    ld C1 = C.x * T.x + C.y * T.y;
    ld A1 = T.x;
    ld B1 = T.y;
    ld C2 = A.x * T.y - T.x * A.y;
    ld A2 = T.y;
    ld B2 = -T.x;
    ld determinant = A1*B2 - B1*A2;
    ld determinant_x = B2*C1 - B1*C2;
    ld determinant_y = A1*C2 - C1*A2;
    ld x = determinant_x / determinant;
    ld y = determinant_y / determinant;
    vec AB(A, B), AX(A, point(x, y));
    vec TO(C, point(x, y));
    TO *= 2;
//    cout << TO * AB << " " << AX % AB << endl;
    cout << TO.B.x << " " << TO.B.y;
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