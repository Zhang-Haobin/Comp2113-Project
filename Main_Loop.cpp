#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "player.h"

using namespace std;

enum class Screen { welcome, lobby, battle, paused, end };
enum class Difficulty { easy, normal, hard }; // todo: add maybe one more

bool is_game_running = true;
int difficulty = 2;
Screen cur_screen = Screen::welcome;

int main() {

    // todo: use something like while(getc()) {} to read keyboard
    //       then the player can skip pressing Enter every time

    while(is_game_running) {
        cout << "SPIRE LITE" << endl;
        cout << "1. Game Start" << endl;
        cout << "2. Options" << endl;
        cout << "3. Quit" << endl;
        cout << "enter the numbers before the entries for selecting" << endl;

        cin >> select_menu;
        if(select_menu == 3) {
            is_game_running = false;
        }
        else if(select_menu == 2) {                                                     
        }
        else if(select_menu == 1) {                                                //开始游戏
            cout << "1. New Game"<< endl;                                              //新开一个存档
            cout << "2. Load"<< endl;      
            cout << "3. Quit"<< endl;                                            //加载一个已有的存档
            cout << "enter the numbers before the entries for selecting"<< endl;
            
            cin >> 
        }
        else {
            cout << "please enter a number in range (1-3)" << endl;
        }
    }
    return 0;
}
