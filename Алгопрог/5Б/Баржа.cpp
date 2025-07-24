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
class linked_stack{
    struct node{
        int value;
        node* prev;
        node(){
            prev = nullptr;
        }
        node(int x, node* prev_){
            value = x;
            prev = prev_;
        }
    };
    int len;
    node* head;
public:
    linked_stack(){
        len = 0;
    }
    void push(int value){
        len++;
        head = new node(value, head);
    }
    void pop(){
        len--;
        node *t = head;
        head = head->prev;
        delete t;
    }
    void clear(){
        while (len > 0){
            pop();
        }
    }
    ~linked_stack(){
        clear();
    }
    int top(){
        return head->value;
    }
    int size(){
        return len;
    }
};
void solve() {
    int n, k, p;
    int size = 0, maxsize = 0;
    cin >> n >> k >> p;
    linked_stack stack[k];
    for (int i = 0; i < n; i++){
        char command;
        int order, type;
        cin >> command >> order >> type;
        order--;
        if (command == '+'){
            stack[order].push(type);
            size++;
            maxsize = max(maxsize, size);
            if (size > p){
                cout << "Error";
                return;
            }
        }
        if (command == '-'){
            if (stack[order].size() == 0){
                cout << "Error";
                return;
            }
            if (stack[order].top() != type){
                cout << "Error";
                return;
            }
            stack[order].pop();
            size--;
        }
    }
    if (size > 0) {
        cout << "Error";
        return;
    }
    cout << maxsize;
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