#include <iostream>
#include <stdio.h>
#include <string>
#include <map>

using namespace std;

int main(){
    string s;
    while (getline(cin, s)){
        string x;
        for (int i = 0; i < s.size(); i++){
            if (isalpha(s[i])){
                x += s[i];
            }
            else {
                for (int i = x.size() - 1; i >= 0; i--){
                    cout << x[i];
                }
                cout << s[i];
                x = "";
            }
        }
    }
}