#include <queue>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
using namespace std;

int main(){
    string s;
    getline(cin, s);
    deque<int> q;
    int a, b;
    for (auto c : s){
        if (isdigit(c)){
            q.push_front(c - '0');
        }
        else if (c != ' '){
            a = q.front();
            q.pop_front();
            b = q.front();
            q.pop_front();
            if (c == '*'){
                q.push_back(a * b);
            }
            if (c == '+'){
                q.push_back(a + b);
            }
            if (c == '-'){
                q.push_back(b - a);
            }
        }
    }
    cout << q.front();
}