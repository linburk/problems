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

void dijkstra(vector<vector<int> > &graph, int start, int finish){
    vector<int> distance(graph.size(), 1e6), past(graph.size());
    vector<bool> markers(graph.size(), 0);
    distance[start] = 0;
    past[start] = -1;
    for (int i = 0; i < graph.size(); i++){
        int vertex = -1;
        for (int j = 0; j < graph.size(); j++){
            if (!markers[j] and (vertex == -1 ? 1 : distance[j] < distance[vertex]))
                vertex = j;
        }
        if (vertex == -1)
            break;
        markers[vertex] = 1;
        for (int j = 0; j < graph.size(); j++){
            if (graph[vertex][j] != -1) {
                int length = graph[vertex][j];
                if (distance[vertex] + length < distance[j]) {
                    distance[j] = distance[vertex] + length;
                    past[j] = vertex;
                }
            }
        }
    }

    if (distance[finish] >= 1e6){
        cout << -1;
        return;
    }
    else {
        vector<int> result;
        int vertex = finish;
        while (vertex != -1){
            result.push_back(vertex + 1);
            vertex = past[vertex];
        }
        for (int i = result.size() - 1; i >= 0; i--)
            cout << result[i] << " ";
        return;
    }
}

int main(){
    int n, start, finish;
    cin >> n >> start >> finish;
    vector<vector<int> > graph(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            cin >> graph[i][j];
            if (graph[i][j] == -1)
                graph[i][j] = 1e6;
        }
    start--; finish--;
    dijkstra(graph, start, finish);
}