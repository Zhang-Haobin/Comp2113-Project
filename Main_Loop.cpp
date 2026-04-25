#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

int main(){
bool game_quit = true, option_quit = true, difficulty_quit = true;
int select_menu = 0, select_option=0, select_difficulty=0;
int difficulty = 2
  
  
  
while (game_quit){                                                   //一级菜单  
game_quit = true;
cout<< "SPIRE LITE" <<endl;
cout<< "1-Game Start" <<endl;
cout<< "2-Options" <<endl;
cout<< "3-Quit" <<endl;
cout<< "enter the numbers before the entries for selecting" <<endl;
cin>>select_menu;
if ( select_menu == "3"){                                                   //退出游戏
    game_quit = false;
}
elif ( select_menu == "2"){                                                     
    option_quit = true;
    while ( option_quit ) {                                              //二级菜单-设置
        cout<<"1-Change Difficulty"<<endl; 
        cout<<"2-Return to Menu"<<endl;
        cout<< "enter the numbers before the entries for selecting" <<endl;
        cin>>select_option;
        if ( select_option == "1" ){
            difficulty_quit = true;
            while ( difficulty_quit ){                                   //三级菜单-难度
            cout<<"1-Journey"<<endl;
            cout<<"2-Classic (Default)"<<endl;
            cout<<"3-Hardcore"<<endl;
            cout<<"4-Return to Options"
                switch (difficulty) {
                    case 1:
                    cout<<"current difficulty: Journey"<<endl;
                    break;
                    case 2:
                    cout<<"current difficulty: Classic"<<endl;
                    break;
                    case 3:
                    cout<<"current difficulty: Hardcore"<<endl;
                    break
                }
            cout<<"enter the numbers before the entries for changing difficulty" <<endl;
            cin>>select_difficulty;
                switch (select_difficulty){
                    case 1:
                        difficulty = 1;
                        cout<<"You have set the difficulty to Journey"
                        break
                    case 2:
                        difficulty = 2;
                        cout<<"You have set the difficulty to Classic"
                        break
                    case 3:
                        difficulty = 3;
                        cout<<"You have set the difficulty to Hardcore"
                        break
                    case 4:                                                          //退出难度
                        difficulty_quit = False
                        select_option = 0
                    default:
                        cout<<"please enter a number in range (1-4)"<<endl;
                        break
                        
                }
            }
        }  
        elif ( select == "2" ){                                           //退出设置
            option_quit = false;
            select_menu = 0;
        }
        else{
            cout<< cout<<"please enter a number in range (1-2) <<endl;
        }
    }
}
else{
    cout<<"please enter a number in range (1-3) <<endl;
}
  


}

}
