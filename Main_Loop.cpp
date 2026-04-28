#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <iomanip>
#include "player.h"

using namespace std;

enum class Screen { welcome, lobby, battle, paused, end };
enum class Menu_page { save_slot, record, info }
enum class Difficulty { easy, normal, hard }; // todo: add maybe one more

bool is_game_running = true;
int difficulty = 2;
Screen cur_screen = Screen::welcome;

void welcomeprocess();
void lobbyprocess();
void battleprocess();
void pausedprocess();

int main() {

    // todo: use something like while(getc()) {} to read keyboard
    //       then the player can skip pressing Enter every time

    while(is_game_running) {
        switch(cur_screen){
            case Screen::welcome:
                welcomeprocess();
                break;
            case Screen::lobby:
                lobbyprocess();
                break
            case Screen::battle:
                battleprocess();
                break
            case Screen::paused:
                pausedprocess();
                break
            case Screen::end:
                is_game_running = false
                break;
        }

void welcomeprocess(){
    cout<<"\n===|Spire Lite|===\n"<<endl;
    cout<<"    Main Menu   "<<endl;
    cout<<"   1-Start      "<<endl;
    cout<<"   2-Game Record"<<endl;
    cout<<"   3-More Info  "<<endl;
    cout<<"   4-Quit       "<<endl;

    



}    
 
        
        
        
        
        
        return 0;
}
