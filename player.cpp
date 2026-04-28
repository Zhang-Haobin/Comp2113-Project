#include "player.h"

Player::get_hp_after_heal(int hp_add) {
	hp += hp_add;
	if (hp > max_hp) {
		hp = max_hp;
	}
	return hp;
}

Player::get_hp_after_hurt(int hp_minus) {
	hp -= hp_minus;
	if (hp < 0) {
		hp = 0;
	}
	return hp;
}

Player::get_damage(int atk) {
	return (atk + damage_boost) * strength;
}
