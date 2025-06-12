#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
using namespace std;

int main()
{
	int n;
	int lastchar = 0, lasti = 0;
	set<long> S;
	cin >> n;

	for (int i = 0; i < n; i++) {
		char c;
		long a;
		cin >> c >> a;
		if (c == '?') {
			lastchar = 1;
			a--;
			if (S.upper_bound(a) != S.end()) {
				lasti = *S.upper_bound(a);
				cout << lasti << endl;
			}
			else
				cout << -1 << endl;
		}
		else {
			if (lastchar) {
				S.insert((a + lasti) % 1000000000);
				lastchar = 0;
			}
			else {
				S.insert(a);
			}
		}
	}
}