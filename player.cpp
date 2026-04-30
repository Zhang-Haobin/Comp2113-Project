#include "player.h"

int Player::get_damage(int atk) const {
	return (atk + damage_boost) * strength;
}

bool Player::is_dead() const {
	return hp <= 0;
}

void Player::heal(const int delta) {
	hp += delta;
	if (hp > max_hp) {
		hp = max_hp;
	}
}

void Player::hurt(const int delta) {
	hp -= delta;
	if (hp < 0) {
		hp = 0;
	}
}
