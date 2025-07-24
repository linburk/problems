#include <iostream>
#include <cmath>

using namespace std;


int main()
{
    string word;
    string words[2];
    int stack[101];
    int index = -1;
    string command;
    while (command != "exit"){
        getline(cin, command);
        int i = 0;
        for (auto c : command){
            
            if (c == ' '){
                words[i] = word;
                i++;
                word = "";
            }
            else 
                word += c;
        }
        words[i] = word;
        if (words[0] == "push"){
            int numb = stoi(words[1]);
            index++;
            stack[index] = numb;
            cout << "ok" << endl;
        }
        if (words[0] == "pop"){
            cout << stack[index] << endl;
            index--;
        }
        if (words[0] == "back"){
            cout << stack[index] << endl;
        }
        if (words[0] == "size"){
            cout << index + 1 << endl;
        }
        if (words[0] == "clear"){
            cout << "ok" << endl;
            index = -1;
            // Ð¸Ð½Ð´ÐµÐºÑ Ð¿ÐµÑÐµÐ¼ÐµÑÐ°ÐµÑÑÑ Ð² Ð½Ð°ÑÐ°Ð»Ð¾, Ð² ÑÑÐµÐºÐµ Ð¾ÑÑÐ°ÑÑÑÑ Ð¼ÑÑÐ¾Ñ
        }
        words[0] = "";
        word = "";
    }
    cout << "bye";
}