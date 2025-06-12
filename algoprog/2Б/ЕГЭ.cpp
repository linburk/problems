#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

int main(){
    string s;
    bool flag = true;
    getline(cin, s);
    string temp = "";
    for (auto x : s){
        if (isdigit(x)){
            temp += x;
        }
        else {
            if (temp != ""){
                int y = stoi(temp);
                if (y > 5) flag = false;
                temp = "";
            }
        }
    }
    if (flag)
        cout << "YES";
    else
        cout << "NO";
}