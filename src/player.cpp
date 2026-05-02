#include "../include/player.h"

// Player damage goes through simple scaling.
int Player::get_damage(int atk) const {
	return (atk + damage_boost) * strength;
}

// Battle checks this after attacks and self-damage cards.
bool Player::is_dead() const {
	return hp <= 0;
}

// Heal but clamp at max HP.
void Player::heal(const int delta) {
	hp += delta;
	if (hp > max_hp) {
		hp = max_hp;
	}
}

// Hurt but clamp at zero HP.
void Player::hurt(const int delta) {
	hp -= delta;
	if (hp < 0) {
		hp = 0;
	}
}
