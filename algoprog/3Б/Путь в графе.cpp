#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<vector<int> > graf(n);
    vector<int> rast(n, -1), put(n, -1);
    queue<int> s;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++){
            int x;
            cin >> x;
            if (x == 1){
                graf[i].push_back(j);
            }
        }
    int a, b;
    cin >> a >> b;
    a--;
    b--;
    s.push(a);
    rast[a] = 0;
    while (!s.empty()){
        int v = s.front();
        s.pop();
        for (int x : graf[v]){
            if (rast[x] == -1){
                s.push(x);
                rast[x] = rast[v] + 1;
                put[x] = v;
            }
        }
    }
    vector<int> ans;
    cout << rast[b] << endl;
    ans.push_back(b);
    while (put[b] != -1){
        b = put[b];
        ans.push_back(b);
    }
    for (int i = ans.size() - 1; i >= 0; i--){
        cout << ans[i] + 1 << " ";
    }
}