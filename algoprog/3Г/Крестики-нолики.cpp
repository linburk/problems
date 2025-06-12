#include <iostream>
#include <vector>
using namespace std;


int main() {
    vector<vector<vector<vector<int> > > > setka(3, vector<vector<vector<int> > > (3, vector<vector<int> >(3, vector<int>(3))));
    vector<vector<char> > setkachar(9, vector<char>(9));

    for (int t, i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            char c;
            cin >> c;
            if (c == 'x')
                t = 1;
            if (c == 'o')
                t = 2;
            if (c == '.')
                t = 0;
            setka[i / 3][j / 3][i % 3][j % 3] = t;
            setkachar[i][j] = c;
        }
    }
    int x, y;
    cin >> x >> y;
    x--; y--;
    x %= 3; y %= 3;
    bool flag = 0;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (setka[x][y][i][j] == 0)
                flag = 1;
        }
    }
    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0 and i != 0)
            cout << endl;
        for (int j = 0; j < 9; j++) {
            if (j % 3 == 0 and j != 0)
                cout << " ";
            if (flag and i / 3 == x and j / 3 == y) {
                if (setkachar[i][j] == '.')
                    cout << "!";
                else
                    cout << setkachar[i][j];
            } else if (!flag) {
                if (setkachar[i][j] == '.')
                    cout << "!";
                else
                    cout << setkachar[i][j];
            } else
                cout << setkachar[i][j];

        }
        cout << endl;
    }
}