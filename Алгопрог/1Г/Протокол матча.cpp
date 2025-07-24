#include <iostream>
#include <string>

using namespace std; 

int main(){
    string s = "";
    int counter[2] = {0}; // Ð¸ÑÐ¾Ð³Ð¾Ð²ÑÐ¹ ÑÑÐµÑ
    int now_player = 0; // Ð¿Ð¾Ð´Ð°ÑÑÐ¸Ð¹
    int last_player = 1; // Ð¿ÑÐ¸Ð½Ð¸Ð¼Ð°ÑÑÐ¸Ð¹
    int count_serv = 0; // ÑÑÐµÑÑÐ¸Ðº Ð¿Ð¾Ð´Ð°Ñ
    int last_serv = 1; // Ð¿Ð¾ÑÐ»ÐµÐ´Ð½Ð¸Ð¹ Ð¿Ð¾Ð´Ð°ÑÑÐ¸Ð¹
    int now_serv = 0; // ÑÐµÐºÑÑÐ¸Ð¹ Ð¿Ð¾Ð´Ð°ÑÑÐ¸Ð¹
    while (s != "eom"){
        cin >> s;
        if (s == "service"){
            count_serv++;
            if (count_serv == 5){
                swap(last_serv, now_serv);
                count_serv = 1;
            } // ÑÐ¼ÐµÐ½Ð° Ð¿Ð¾Ð´Ð°ÑÑÐµÐ³Ð¾
            else {
                now_player = now_serv;
                last_player = last_serv;
            } // Ð¿Ð¾Ð´Ð°ÐµÑ ÑÐµÐºÑÑÐ¸Ð¹ Ð¿Ð¾Ð´Ð°ÑÑÐ¸Ð¹
        } // Ð¿Ð¾Ð´Ð°ÑÐ°
        else if (s == "net"){
            counter[last_player]++;
        } // ÑÐµÐºÑÑÐ¸Ð¹ Ð¿Ð¾Ð¿Ð°Ð» Ð² ÑÐµÑÐºÑ, ÑÑÐµÑ+ Ð¿ÑÐµÐ´ Ð¸Ð³ÑÐ¾ÐºÑ 
        else if (s == "goal"){
            counter[now_player]++;
        } // ÑÐµÐºÑÑÐ¸Ð¹ Ð·Ð°Ð±Ð¸Ð» Ð³Ð¾Ð», ÑÑÐµÑ+ ÐµÐ¼Ñ
        else if (s == "return"){
            swap(now_player, last_player);
        } // Ð¸Ð³ÑÐ¾Ðº Ð¾ÑÐ±Ð¸Ð²Ð°ÐµÑ, Ð¸Ð³ÑÐ°ÐµÑ Ð²ÑÐ¾ÑÐ¾Ð¹ Ð¸Ð³ÑÐ¾Ðº
        else if (s == "out"){
            counter[last_player]++; 
            swap(now_player, last_player);
        } // Ð¼ÑÑ Ð² Ð°ÑÑÐµ, Ð¿ÑÐµÐ´ÑÐ´ÑÑÐµÐ¼Ñ ÑÑÐµÑ+
    }
    cout << counter[0] << " " << counter[1];
}