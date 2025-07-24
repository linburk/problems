#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	int n, m;
	cin >> n >> m;
	vector<vector<int> > graf(n, vector<int>(n, 0));
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--;
		b--;
		graf[a][b] = 1;
		graf[b][a] = 1;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int z = 0; z < n; z++) {
				if (z != j and graf[i][z] == 1 and graf[i][j] == 1) {
					if (graf[j][z] == 0) {
						cout << "NO";
						return 0;
					}
				}
			}
		}
	}
	cout << "YES";
}