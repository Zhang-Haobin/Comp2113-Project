#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "player.h"
#include "save.h"

using namespace std;

enum class Screen { welcome, lobby, battle, paused, end };                  
enum class Difficulty { easy, normal, hard, lunatic }; 

bool is_game_running = true;
int difficulty = 2;
Screen cur_screen = Screen::welcome;

void welcomeprocess();                              
void lobbyprocess();
void battleprocess();
void pausedprocess();

void save_slotprocess();
void recordprocess();
void infoprocess();

int main() {

while(is_game_running) {
    switch(cur_screen){
        case Screen::welcome:
            welcomeprocess();
            break;
        case Screen::lobby:
            lobbyprocess();
            break;
        case Screen::battle:
            battleprocess();
            break;
        case Screen::paused:
            pausedprocess();
            break;
        case Screen::end:
            is_game_running = false;
            break;
    }

return 0;
}

//this is welcome page
void welcomeprocess(){

cout<<"\n===|Spire Lite|===\n"<<endl;
cout<<"    Main Menu   "<<endl;
cout<<"   1-Start      "<<endl;
cout<<"   2-Game Record"<<endl;
cout<<"   3-More Info  "<<endl;
cout<<"   4-Quit       "<<endl;

int choice;
cin>>choice;
switch (choice){
    case 1:
        save_slotprocess();
        break;
    case 2:
        recordprocess();
        break;
    case 3:
        infoprocess();
        break;
    case 4:
        cur_screen = Screen::end;
        break;
    default:
        cout<<"Invalid Choice"<<endl;
        break;
    }
}    
 
void save_slotprocess()
        
        
        
        


