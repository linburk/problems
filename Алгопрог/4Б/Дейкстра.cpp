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

int dijkstra(vector<vector<int> > &graph, int start, int finish){
    vector<int> distance(graph.size(), 1e6);
    vector<bool> markers(graph.size(), 0);
    distance[start] = 0;
    for (int i = 0; i < graph.size(); i++){
        int vertex = -1;
        for (int j = 0; j < graph.size(); j++){
            if (!markers[j] and (vertex == -1 ? 1 : distance[j] < distance[vertex]) and distance[j] != -1)
                vertex = j;
        }
        if (distance[vertex] == 1e6)
            break;
        markers[vertex] = 1;
        for (int j = 0; j < graph.size(); j++){
            int length = graph[vertex][j];
            distance[j] = min(distance[vertex] + length, distance[j]);
        }
    }
    return distance[finish];

}

int main(){
    int n, start, finish;
    cin >> n >> start >> finish;
    vector<vector<int> > graph(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> graph[i][j];
    start--; finish--;
    cout << dijkstra(graph, start, finish);
}