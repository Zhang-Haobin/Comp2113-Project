#include <string>
#include <cstdlib>
#include "enemy.h"

using namespace std;

Enemy::Enemy() { // default constructor: default enemy
    name = "unknown";
    max_hp = 15;
    hp = 15;
    attack = 5;
    armor = 0;
}

Enemy::Enemy(string name, int max_hp, int attack, int armor) { // custom enemy
    this->name = name;
    this->max_hp = max_hp;
    this->hp = max_hp;
    this->attack = attack;
    this->armor = armor;
}

void Enemy::take_damage(int attack) {
    int real_damage = attack - armor;
    if (real_damage < 0){
        real_damage = 0;
    }
    hp -= real_damage;
    if (hp <= 0){
        hp = 0;
    }
}

int Enemy::get_attack() const {
    return attack;
}

bool Enemy::is_dead() const {
    return hp <= 0;
}

Enemy Enemy::create_Cultist() {
    return Enemy("Cultist", 20, 5, 0);
}

Enemy Enemy::create_JawWorm() {
    return Enemy("Jaw Worm", 30, 7, 0);
}

Enemy Enemy::create_Louses() {
    return Enemy("Louses", 18, 6, 0);
}

Enemy Enemy::create_Slime() {
    return Enemy("Slime", 14, 4, 0);
}

Enemy Enemy::create_Sentry() {
    return Enemy("Sentry", 35, 8, 2);
}

Enemy Enemy::create_GremlinNob() {
    return Enemy("Gremlin Nob", 45, 10, 1);
}

Enemy Enemy::create_Boss() {
    return Enemy("Boss", 60, 12, 0);
}

Enemy create_normal_enemy_by_floor(int floor) {
    int random_number = rand() % 100;

    if (floor <= 3) {
        if (random_number < 45) {
            return Enemy::create_Slime();
        }
        else if (random_number < 75) {
            return Enemy::create_Louses();
        }
        else {
            return Enemy::create_Cultist();
        }
    }

    if (floor <= 7) {
        if (random_number < 35) {
            return Enemy::create_Cultist();
        }
        else if (random_number < 75) {
            return Enemy::create_JawWorm();
        }
        else {
            return Enemy::create_Sentry();
        }
    }

    if (random_number < 30) {
        return Enemy::create_JawWorm();
    }
    else if (random_number < 70) {
        return Enemy::create_Sentry();
    }
    else {
        return Enemy::create_GremlinNob();
    }
}

Enemy create_boss_enemy() {
    return Enemy::create_Boss();
}
