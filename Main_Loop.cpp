#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "player.h"
using namespace std;

int main(){
    bool game_quit = true, option_quit = true, difficulty_quit = true;
    int select_menu = 0, select_option=0, select_difficulty=0;
    int difficulty = 2;
  
  
while (game_quit){                                                   //一级菜单  
    game_quit = true;
    cout<< "SPIRE LITE" <<endl;
    cout<< "1-Game Start" <<endl;
    cout<< "2-Options" <<endl;
    cout<< "3-Quit" <<endl;
    cout<< "enter the numbers before the entries for selecting" <<endl;
    cin>>select_menu;
    if ( select_menu == 3){                                                   //退出游戏
        game_quit = false;
    }
else if ( select_menu == 2){                                                     
}
else if ( select_menu == 1){                                                //开始游戏
    cout<< "1-New Game"<<endl;                                              //新开一个存档
    cout<< "2-Load"<<endl;      
    cout<< "3-Quit"<<endl;                                            //加载一个已有的存档
    cout<< "enter the numbers before the entries for selecting"<<endl;
    while 


}
else{
    cout<<"please enter a number in range (1-3)"<<endl;
}


}

return 0
}
