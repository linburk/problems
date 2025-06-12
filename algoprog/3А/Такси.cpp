#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool comp(int a, int b){
    return b <= a;
}

int main(){
    int n;
    cin >> n;

    vector<int> s(n);
    vector<int> scopy(n);

    vector<int> t(n);
    vector<int> tcopy(n);

    vector<int>::iterator is;
    vector<int>::iterator it;
    
    for (int i = 0; i < n; i++){
        cin >> s[i];
    }

    for (int i = 0; i < n; i++){
        cin >> t[i];
    }

    scopy = s;
    tcopy = t;

    sort(scopy.begin(), scopy.end());
    sort(tcopy.begin(), tcopy.end(), comp);

    for (int i = 0; i < n; i++)
    {
        int x = s[i];
        is = find(scopy.begin(), scopy.end(), x);
        int xi = distance(scopy.begin(), is);

        int y = tcopy[xi];
        it = find(t.begin(), t.end(), y);
        int yi = distance(t.begin(), it);

        cout << yi + 1 << " ";
    }
}