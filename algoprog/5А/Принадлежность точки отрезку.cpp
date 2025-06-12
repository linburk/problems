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

        point(long double x, long double y) : x(x), y(y) {}

        long double length() {
            return std::hypot(x, y);
        }

        long double radangle() {
            return std::atan2(y, x);
        }

        point &operator=(int null) {
            x = 0, y = 0;
            return (*this);
        }

        point operator-() { return point(-(this->x), -(this->y)); }

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

    };

    const long double operator*(const point &A, const point &B) { return A.x * B.x + A.y * B.y; } // ÑÐºÐ°Ð»ÑÑÐ½Ð¾Ðµ Ð¿Ñ.

    const long double operator%(const point &A, const point &B) { return A.x * B.y - A.y * B.x; }; // Ð²ÐµÐºÑÐ¾ÑÐ½Ð¾Ðµ Ð¿Ñ.

    std::istream &operator>>(std::istream &is, point &A) {
        is >> A.x >> A.y;
        return is;
    }

    long double radangle(point &A, point &B) {
        return (atan2(A % B, A * B));
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
        return S;
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
    point A, B, C;
    cin >> C >> A >> B;
    B -= A;
    C -= A;
    if ((ll)(B % C) == 0 and (ll)(B * C) >= 0) {
        B += A;
        C += A;
        A -= B;
        C -= B;
        if ((ll)(A * C) >= 0) {
            cout << "YES";
            return;
        }
    }
    cout << "NO";
}

int32_t main() {
    $FASTSTREAM
    solve();
}