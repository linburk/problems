#include <queue>
#include <deque>
#include <iostream>
#include <set>
#include <algorithm>
#include <string>
#include <cmath>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <stack>
#include <list>
#include <iterator>
using namespace std;

int dijksta(vector<vector<int> > &graph, vector<int> &cost, int start, int finish){
    vector<bool> markers(graph.size(), 0);
    vector<int> distance(graph.size(), 1e9);
    distance[start] = 0;
    for (int i = 0; i < graph.size(); i++){
        int vertex = -1;
        for (int j : graph[i]){
            if (!markers[j] and (vertex == -1 or distance[vertex] > distance[j])){
                vertex = j;
            }
        }
        if (vertex == -1)
            break;
        markers[vertex] = 1;
        for (int j : graph[i]){
            distance[j] = min(distance[vertex] + cost[vertex], distance[j]);
        }
    }
    return distance[finish];
}

int main() {
    int n;
    cin >> n;
    vector<int> cost(n);
    for (int i = 0; i < n; i++)
        cin >> cost[i];
    int m;
    cin >> m;
    vector<vector<int> > graph(n);
    for (int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        a--; b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    int answer = dijksta(graph, cost, 0, n - 1);
    if (answer == 1e9)
        cout << -1;
    else
        cout << answer;
}