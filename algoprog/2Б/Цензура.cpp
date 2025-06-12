#include <iostream>
#include <vector>
#include <string>
#include <set>
using namespace std;

vector<string> words(string s){
    vector<string> a;
    string temp;
    for (char i : s){
        if (isalpha(i))
            temp += i;
        else if (temp.size() != 0) {
            a.push_back(temp);
            temp = "";
        }
    }
    if (temp.size() != 0)
        a.push_back(temp);
    return a;
}

int checkword(string word){
    set<char> enter;
    for (char x : word){
        enter.insert(x);
    }
    if (enter.size() <= 3)
        return 0;
    return 1;
}

bool check(vector<string> a, string s){
    int count = 0;
    for (string x : a){
        count += checkword(x);
    }
    if (count <= a.size() - count){
        return 0;
    }
    return 1;
}

int main(){
    string s;
    while (getline(cin, s)){
        vector<string> a = words(s);
        if (check(a, s)){
            cout << s;
        }
    }
}