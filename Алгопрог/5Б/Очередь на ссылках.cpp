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

class linked_queue{
    struct node{
        int value;
        node *next;
        node *last;
        node(){
            next = nullptr;
            last = nullptr;
        }
        node(int x, node *next_){
            last = nullptr;
            next = next_;
            value = x;
        }
    };
    int len;
    node *head;
    node *last;
public:
    linked_queue(){
        head = new node();
        last = head;
        len = 0;
    }

    void push(int value){
        len++;
        last->last = new node(value, last);
        last = last->last;
        if (len == 1){
            head = last;
        }
    }
    void pop(){
        len--;
        head = head->last;
        if (len == 0)
            delete head;
        else
            delete head->next;
    }
    void clear(){
        while (len > 0){
            pop();
        }
    }
    int front(){
        return head->value;
    }
    int size(){
        return len;
    }
    ~linked_queue(){
        clear();
    }
};

void solve() {
    linked_queue q;
    string command;
    while (getline(cin, command)){
        string word, val;
        int i = 0;
        for (; i < command.size(); i++){
            if (command[i] == ' '){
                i++;
                for (; i < command.size(); i++)
                    val += command[i];
                break;
            }
            word += command[i];
        }
        if (word == "push"){
            int x = stoi(val);
            q.push(x);
            cout << "ok" << endl;
        }
        if (word == "pop"){
            if (q.size() > 0) {
                cout << q.front() << endl;
                q.pop();
            }
            else
                cout << "error" << endl;
        }
        if (word == "front"){
            if (q.size() > 0) {
                cout << q.front() << endl;
            }
            else
                cout << "error" << endl;
        }
        if (word == "size"){
            cout << q.size() << endl;
        }
        if (word == "clear"){
            q.clear();
            cout << "ok" << endl;
        }
        if (word == "exit"){
            cout << "bye";
            exit(0);
        }
    }
}

int32_t main() {
    setlocale(LC_ALL, "Russian");
#ifndef __APPLE__
    $FASTSTREAM
#endif
    solve();
    return 0;
}