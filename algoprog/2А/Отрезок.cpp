#include <iostream>
using namespace std;

int main(){
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    c -= a;
    d -= b;
    a = c;
    b = d;
    while (b != 0) {
		a = a % b;
		swap(a, b);
	}
    cout << c + d - a;
}