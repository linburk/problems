#include <iostream>
#include <cmath>

using namespace std;


int main()
{
    int queue[2000];
    int indexhead = 0, indexend = 0;
    string command;
    while (command != "exit"){
        cin >> command;
        if (command == "push"){
            int numb;
            cin >> numb;
            queue[indexend] = numb;
            indexend++;
            cout << "ok" << endl;
        }
        if (command == "pop"){
            if (indexhead == indexend){
                cout << "error" << endl;
            }
            else {
                cout << queue[indexhead] << endl;
                indexhead++;
            }
        }
        if (command == "front"){
            if (indexhead == indexend){
                cout << "error" << endl;
            }
            else {
                cout << queue[indexhead] << endl;
            }
        }
        if (command == "size"){
            cout << indexend - indexhead << endl;
        }
        if (command == "clear"){
            cout << "ok" << endl;
            indexend = 0;
            indexhead = 0;
        }
    }
    cout << "bye";
}