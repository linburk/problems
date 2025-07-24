#include <iostream>
using namespace std;

int main(){
    string s;
    getline(cin, s);
    int mask = 0;
    for (auto c : s){
        if (mask & (1 << (c - '0'))){
            cout << c;
            break;
        }
        mask += (1 << (c - '0'));
    }
}