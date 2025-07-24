#include <iostream>
#include <string>
using namespace std;


int main(){
    string s;
    getline(cin, s);
    int count = 0;
    bool roshiza = false;
    bool morda = false;
    bool ulibka = false;
    string ulibki = "[]()";
    for (int i = 0; i < s.size(); i++){
        if (s[i] == ':' or s[i] == ';'){
            roshiza = true;
        }
        else if (roshiza and s[i] == '-'){
            morda = true;
        }
        else if (roshiza and (ulibki.find(s[i]) != string::npos)){
            ulibka = true;
            morda = true;
        }
        else {
            ulibka = false;
            roshiza = false;
            morda = false;
        }

        if (roshiza and ulibka and morda){
            count++;
            roshiza = false;
            morda = false;
            ulibka = false;
        }
    }
    cout << count;
}