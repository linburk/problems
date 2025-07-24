// created by vim 29/03/2024
#include <bits/stdc++.h>
using namespace std;

static vector<bool> win(101, 0), lose(101, 0), used(101, 0);
static vector<int> degree(101, 0);

static inline vector<vector<int> > buildGraph(){
	vector<vector<int> > graph(101);
	for (int i = 0; i < 101; i++){
		if (i % 3 == 0){
			if (i > 0){
			graph[i - 1].push_back(i);
			degree[i]++;
			}
			if (i > 1){
			graph[i - 2].push_back(i);
			degree[i]++;
			}
		}
		if (i % 3 == 1){
			if (i > 0){
			graph[i - 1].push_back(i);
			degree[i]++;
			}
			if (i > 2){
			graph[i - 3].push_back(i);
			degree[i]++;
			}
		}
		if (i % 3 == 2){
			if (i > 0){
			graph[i - 1].push_back(i);
			degree[i]++;
			}
			if (i > 1){
			graph[i - 2].push_back(i);
			degree[i]++;
			}
			if (i > 2){
			graph[i - 3].push_back(i);
			degree[i]++;
			}
		}
	}
	return graph;
}

static vector<vector<int> > graph = buildGraph();

void dfs(int v){
	if (used[v]) return;
	used[v] = 1;
	for (auto to : graph[v]){
		if (!used[to]){
			if (lose[v]) win[to] = 1;
			else if (--degree[to] == 0) lose[to] = 1;
			else continue;
			dfs(to);
		}
	}
}

int32_t  main(){
	lose[0] = 1;;
	dfs(0);
	int n;
	cin >> n;
	cout << (!lose[n] & win[n] ? 1 : 2);
//	for (int i = 0; i <= 100; i++){
//		cout << (!lose[i] & win[i] ? 1 : 2) << '\n';
//	}
}