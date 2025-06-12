#include <iostream>
using namespace std;


void hanoy(int n, int a, int b) {
	if (n != 0) {
		hanoy(n - 1, a, 2);
		cout << n << " " << a << " " << b << endl;
		hanoy(n - 1, 2, b);
	}
}

int main() {
	int n;
	cin >> n;
	hanoy(n, 1, 3);
}