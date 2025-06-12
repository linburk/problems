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

vector<vector<int> > cube222(7, vector<int>(5));

bool check(vector<vector<int> > &cube){
    for (int i = 1; i <= 6; i++){
        for (int j = 2; j <= 4; j++){
            if (cube[i][j] != cube[i][j - 1])
                return 0;
        }
    }
    return 1;
}

bool rotate1(){
    vector<vector<int> > cube = cube222, cubecopy = cube222;
    cube[2][1] = cubecopy[4][1];
    cube[2][2] = cubecopy[4][2];
    cube[5][1] = cubecopy[2][1];
    cube[5][2] = cubecopy[2][2];
    cube[6][1] = cubecopy[5][1];
    cube[6][2] = cubecopy[5][2];
    cube[4][1] = cubecopy[6][1];
    cube[4][2] = cubecopy[6][2];
    cubecopy = cube;
    if (check(cube))
        return 1;
    for (int i = 0; i < 2; i++){
        cube[2][1] = cubecopy[4][1];
        cube[2][2] = cubecopy[4][2];
        cube[5][1] = cubecopy[2][1];
        cube[5][2] = cubecopy[2][2];
        cube[6][1] = cubecopy[5][1];
        cube[6][2] = cubecopy[5][2];
        cube[4][1] = cubecopy[6][1];
        cube[4][2] = cubecopy[6][2];
        cubecopy = cube;
    }
    if (check(cube)){
        return 1;
    }
    return 0;
}
bool rotate2(){
    vector<vector<int> > cube = cube222, cubecopy = cube222;
    cube[4][2] = cubecopy[1][4];
    cube[4][4] = cubecopy[1][3];
    cube[3][2] = cubecopy[1][4];
    cube[3][2] = cubecopy[1][4];
    cube[5][2] = cubecopy[1][4];
    cube[5][2] = cubecopy[1][4];
    cube[1][2] = cubecopy[1][4];
    cube[1][2] = cubecopy[1][4];
    cubecopy = cube;
    if (check(cube))
        return 1;
    for (int i = 0; i < 2; i++){
        cube[4][2] = cubecopy[1][4];
        cube[4][4] = cubecopy[1][3];
        cube[3][2] = cubecopy[1][4];
        cube[3][2] = cubecopy[1][4];
        cube[5][2] = cubecopy[1][4];
        cube[5][2] = cubecopy[1][4];
        cube[1][2] = cubecopy[1][4];
        cube[1][2] = cubecopy[1][4];
        cubecopy = cube;
    }
    if (check(cube)){
        return 1;
    }
    return 0;
}
bool rotate3(){
    vector<vector<int> > cube = cube222, cubecopy = cube222;
    cube[2][3] = cubecopy[4][3];
    cube[2][4] = cubecopy[4][4];
    cube[5][3] = cubecopy[2][3];
    cube[5][4] = cubecopy[2][4];
    cube[6][3] = cubecopy[5][3];
    cube[6][4] = cubecopy[5][4];
    cube[4][3] = cubecopy[6][3];
    cube[4][4] = cubecopy[6][4];
    cubecopy = cube;
    if (check(cube))
        return 1;
    for (int i = 0; i < 2; i++){
        cube[2][3] = cubecopy[4][3];
        cube[2][4] = cubecopy[4][4];
        cube[5][3] = cubecopy[2][3];
        cube[5][4] = cubecopy[2][4];
        cube[6][3] = cubecopy[5][3];
        cube[6][4] = cubecopy[5][4];
        cube[4][3] = cubecopy[6][3];
        cube[4][4] = cubecopy[6][4];
        cubecopy = cube;
    }
    if (check(cube)){
        return 1;
    }
    return 0;
}
bool rotate4(){
    vector<vector<int> > cube = cube222, cubecopy = cube222;
    cube[1][1] = cubecopy[2][1];
    cube[1][3] = cubecopy[2][3];
    cube[2][1] = cubecopy[3][1];
    cube[2][3] = cubecopy[3][3];
    cube[3][1] = cubecopy[6][4];
    cube[3][3] = cubecopy[6][2];
    cube[6][2] = cubecopy[1][3];
    cube[6][4] = cubecopy[1][1];
    cubecopy = cube;
    if (check(cube))
        return 1;
    for (int i = 0; i < 2; i++){
        cube[1][1] = cubecopy[2][1];
        cube[1][3] = cubecopy[2][3];
        cube[2][1] = cubecopy[3][1];
        cube[2][3] = cubecopy[3][3];
        cube[3][1] = cubecopy[6][4];
        cube[3][3] = cubecopy[6][2];
        cube[6][2] = cubecopy[1][3];
        cube[6][4] = cubecopy[1][1];
        cubecopy = cube;
    }
    if (check(cube)){
        return 1;
    }
    return 0;
}
bool rotate5(){
    vector<vector<int> > cube = cube222, cubecopy = cube222;
    cube[2][2] = cubecopy[3][2];
    cube[2][4] = cubecopy[3][4];
    cube[3][2] = cubecopy[6][3];
    cube[3][4] = cubecopy[6][1];
    cube[6][1] = cubecopy[1][4];
    cube[6][3] = cubecopy[1][2];
    cube[1][2] = cubecopy[2][2];
    cube[1][4] = cubecopy[2][4];
    cubecopy = cube;
    if (check(cube))
        return 1;
    for (int i = 0; i < 2; i++){
        cube[2][2] = cubecopy[3][2];
        cube[2][4] = cubecopy[3][4];
        cube[3][2] = cubecopy[6][3];
        cube[3][4] = cubecopy[6][1];
        cube[6][1] = cubecopy[1][4];
        cube[6][3] = cubecopy[1][2];
        cube[1][2] = cubecopy[2][2];
        cube[1][4] = cubecopy[2][4];
        cubecopy = cube;
    }
    if (check(cube)){
        return 1;
    }
    return 0;
}
bool rotate6(){
    vector<vector<int> > cube = cube222, cubecopy = cube222;
    cube[1][1] = cubecopy[5][2];
    cube[1][2] = cubecopy[5][4];
    cube[5][2] = cubecopy[3][4];
    cube[5][4] = cubecopy[3][3];
    cube[3][4] = cubecopy[4][3];
    cube[3][3] = cubecopy[4][1];
    cube[4][3] = cubecopy[1][1];
    cube[4][1] = cubecopy[1][2];
    cubecopy = cube;
    if (check(cube))
        return 1;
    for (int i = 0; i < 2; i++){
        cube[1][1] = cubecopy[5][2];
        cube[1][2] = cubecopy[5][4];
        cube[5][2] = cubecopy[3][4];
        cube[5][4] = cubecopy[3][3];
        cube[3][4] = cubecopy[4][3];
        cube[3][3] = cubecopy[4][1];
        cube[4][3] = cubecopy[1][1];
        cube[4][1] = cubecopy[1][2];
        cubecopy = cube;
    }
    if (check(cube)){
        return 1;
    }
    return 0;
}
void solve() {
    for (int i = 1; i <= 6; i++)
        for (int j = 1; j <= 4; j++)
            cin >> cube222[i][j];
    cout << ( ( rotate1() | rotate2() | rotate3() | rotate4() | rotate5() | rotate6() | check(cube222) ) ? "YES" : "NO") << endl;
}

int32_t main() {
    setlocale(LC_ALL, "Russian");
#ifndef __APPLE__
    std::cin.tie(0);
    std::cout.tie(0);
    std::ios_base::sync_with_stdio(false);
#endif
//    int t;
//    cin >> t;
//    for (int i = 0; i < t; i++)
    solve();
    return 0;
}