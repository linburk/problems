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

int dijkstra(vector<vector<pair<int, int> > > &graph, int start, int finish){
    vector<int> distance(graph.size(), 1e9);
    vector<bool> markers(graph.size(), 0);
    distance[start] = 0;
    for (int i = 0; i < graph.size(); i++){
        int vertex = -1;
        for (int j = 0; j < distance.size(); j++){
            if (!markers[j] and (vertex == -1 or distance[j] < distance[vertex]))
                vertex = j;
        }
        if (vertex == -1)
            break;
        markers[vertex] = 1;
        for (int j = 0; j < graph.size(); j++){
            if (graph[vertex][j] != make_pair(-1, -1)){
                int length = (distance[vertex] <= graph[vertex][j].first ? graph[vertex][j].second : 1e9);
                distance[j] = min(distance[j], length);
            }
        }
    }
    return distance[finish];
}


int main() {
    int n;
    cin >> n;
    int start, finish;
    cin >> start >> finish;
    start--; finish--;
    int races;
    cin >> races;
    vector<vector<pair<int, int> > > graph(n, vector<pair<int, int> >(n, make_pair(-1, -1)));
    for (int i = 0; i < races; i++){
        int from, to, whenfrom, whento;
        cin >> from >> whenfrom >> to >> whento;
        from--; to--;
        graph[from][to] = {whenfrom, whento};
    }
    int answer = dijkstra(graph, start, finish);
    cout << (answer == 1e9 ? -1 : answer);
}