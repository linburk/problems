#include <iostream>
using namespace std;


string ABACABA(int a, char s) {
	if (a == 1) return "A";
	return ABACABA(a - 1, s) + char(s + a) + ABACABA(a - 1, s);
}

int main() {
	int a;
	char s = 'A' - 1;
	cin >> a;
	cout << ABACABA(a, s);
}