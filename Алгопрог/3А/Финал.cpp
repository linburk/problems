#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <map>
using namespace std;

int main()
{
	int P, N, k;
	cin >> P >> N >> k;

	map<string, int> check;
	vector<string> teamnames(P);
	vector<int> numbers(P);
	vector<int> ans;
	string word;
	getline(cin, word);
	for (int i = 0; i < P; i++) {
		getline(cin, teamnames[i]);
		check[teamnames[i]] = 0;
	}

	for (int i = 0; i < P; i++) {
		cin >> numbers[i];
	}

	
	for (int i = 0; i < P; i++) {
		if (check[teamnames[i]] < k) {
			ans.push_back(i);
			check[teamnames[i]]++;
		}
	}

	if (ans.size() < N)
		N = ans.size();

	for (int i = 0; i < N; i++) {
		cout << teamnames[ans[i]] << " #" << numbers[ans[i]] << endl;
	}
}