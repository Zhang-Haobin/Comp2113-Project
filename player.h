#ifndef PLAYER_H
#define PLAYER_H

#include <string>

using namespace std;
struct player{                  //玩家的状态
    string name;                 //名称
    int max_hp = 60;                  //最大生命值
    int hp = 60;                      //当前生命值
    int max_energy = 3;              //最大能量
    int energy = 3;                  //当前能量
    int strength = 1;                //伤害倍率
    int damage_boost = 0;            //伤害增加
    int armor = 0;                   //伤害减免值
    int stage = 0;                   //当前处于的层数
    int max_card = 6;                //卡牌上限
    int heal(int hp_add){        //回血函数
        hp += hp_add;
        if (hp > max_hp){
            hp = max_hp;
        }
        return hp;
    }

    int hurt(int hp_minus){          //扣血函数
        hp -= hp_minus
        if (hp < 0){
            hp = 0;
        }
        return hp;
    }
    
    int attack(int atk){                              //计算buff后的伤害函数
        return (atk + damage_boost) * strength;
    }

   


}

#endif