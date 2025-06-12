#include <queue>
#include <deque>
#include <iostream>
#include <set>
#include <algorithm>
#include <string>
#include <cmath>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <stack>
#include <list>
#include <iterator>
#include <iomanip>
#include <stdio.h>
#include <bitset>

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
#define $FASTSTREAM std::cin.tie(0); std::cout.tie(0); std::ios_base::sync_with_stdio(false);

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

        const long double operator*(const point &A) const { return (this->x) * A.x + (this->y) * A.y; }

        const long double operator%(const point &A) const { return (this->x) * A.y - (this->y) * A.x; }



    };

    std::istream &operator>>(std::istream &is, point &A) {
        is >> A.x >> A.y;
        return is;
    }

    long double radangle(const point &A, const point &B) {
        long double scal = A * B, vect = A % B;

        if (scal == 0){
            if (vect > 0)
                return std::atan(1) * 2;

            if (vect < 0)
                return std::atan(1) * -2;
        }

        if (scal > 0)
            return std::atan(vect / scal);

        if (scal < 0){
            if (vect >= 0)
                return std::atan(vect / scal) + std::atan(1) * 4;

            if (vect < 0)
                return std::atan(vect / scal) - std::atan(1) * 4;
        }

        return 0;
    }

    long double length(point &A, point &B) {
        return std::hypot((A.x - B.x), (A.y - B.y));
    }

    long double area(vector<point> shape) {
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
            A *= q, B *= q;
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

        const long double operator*(const vec &C) {
            const point AT = B - A;
            const point BT = C.B - C.A;
            return AT * BT;
        }

        const long double operator%(const vec &C) {
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

namespace tools {

    template<typename T>
    T gcd(T a, T b){
        while (b > 0){
            a %= b;
            std::swap(a, b);
        }
        return a;
    }

    template<typename T>
    T lcm(T a, T b) {
        return a * b / gcd(a, b);
    }

    template<typename T>
    std::istream &operator>>(std::istream &is, std::vector<T> &array){
        for (auto &i : array){
            is >> i;
        }
        return is;
    }

    template<typename T>
    std::ostream &operator<<(std::ostream &os, const std::vector<T> &array){
        for (const auto& i : array){
            os << i << " ";
        }
        return os;
    }

    template<typename T>
    std::istream &operator>>(std::istream &is, std::vector<std::vector<T> > &matrix) {
        for (auto &i: matrix)
            for (auto &j: i)
                is >> j;
        return is;
    }

    template<typename T>
    std::ostream &operator<<(std::ostream &os, const std::vector<std::vector<T> > &matrix) {
        for (const auto &i : matrix) {
            for (const auto &j: i)
                os << j << " ";
            os << "\n";
        }
        return os;
    }

}

using namespace tools;

using namespace vectors;

void solve(){
    point A, B, C, D;
    cin >> A >> B >> C >> D;
    if (vec{A, B} % vec{C, D} == 0){
        if (vec{A, B} == vec{C, D})
            cout << 2;
        else
            cout << 0;
        return;
    }
    ld A1 = B.x - A.x, B1 = A.y - B.y; ld C1 = A1 * A.y + B1 * A.x; // Ay + Bx = C
    ld A2 = D.x - C.x, B2 = C.y - D.y; ld C2 = A2 * C.y + B2 * C.x;
    ld y = (B1 * C2 - B2 * C1) / (A2 * B1 - A1 * A2);
    ld x = (C1 - A1 * y) / B1;
    cout << 1 << setprecision(7) << fixed <<  " " << x << " " << y;
}

int32_t main() {
#ifndef __APPLE__
    $FASTSTREAM
#endif
    solve();
}