#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	int n;
	cin >> n;
	vector<vector<int> > graf(n, vector<int>(n));
	vector<int> stok;
	vector<int> istok;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> graf[i][j];
	
	for (int i = 0; i < n; i++) {
		int stokcheck = 0, istokcheck = 0;
		for (int j = 0; j < n; j++) {
			stokcheck += graf[i][j];
			istokcheck += graf[j][i];
		}
		if (stokcheck == 0)
			stok.push_back(i);
		if (istokcheck == 0)
			istok.push_back(i);
	}
	cout << istok.size() << endl;
	for (auto x : istok)
		cout << x + 1 << endl;
	cout << stok.size() << endl;
	for (auto x : stok)
		cout << x + 1 << endl;
}