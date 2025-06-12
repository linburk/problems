#include <iostream>
#include <string>
using namespace std;


string stroka(string s){
	string l = s.substr(0, 1) + "(";
	string r = ")" + s.substr(s.size() - 1, 1);
	if (s.size() == 1 || s.size() == 2) {
		string m = "(" + s + ")";
		return m;
	}
	string i = s.substr(1, s.size() - 2);
	string x = l + stroka(i) + r;
	return x;
}

int main() {
	string s;
	getline(cin, s);
	cout << stroka(s);
}