#include "../include/combat_utils.h"
#include "../include/Cardfactory.h"
#include <iostream>
#include <cstdlib>

using namespace std;

// Reset the player's turn in the older helper style.
void reset_player_turn(Player &player) {
    player.energy = player.max_energy;
    draw_cards(player, 5);
    cout << "Turn reset. Energy: " << player.energy << "/" << player.max_energy << "\n";
}

// Placeholder draw helper kept from the earlier design.
void draw_cards(Player &player, int count) {
    // Placeholder for full deck system
    if (player.cards.size() < player.max_card) {
        // Will expand later
    }
}

// Apply one enemy attack and spend block first.
void apply_enemy_attack(Player &player, const Enemy &enemy) {
    int damage = enemy.get_attack();
    
    if (player.block >= damage) {
        player.block -= damage;
        damage = 0;
        cout << "Block absorbed all damage!\n";
    } 
    else {
        damage -= player.block;
        player.block = 0;
        cout << enemy.name << " dealt " << damage << " damage!\n";
    }
    
    if (damage > 0) {
        player.hurt(damage);
    }
}

// Check if the player is dead or all enemies are gone.
bool is_battle_over(const Battle &battle) {
    if (battle.player.is_dead()) return true;
    
    for (const Enemy &enemy : battle.enemies) {
        if (!enemy.is_dead()) return false;
    }
    return true;
}

// Older reward helper, similar to the reward logic now inside Battle.
void grant_battle_rewards(Player &player, int &score) {
    cout << "\n=== Victory! ===\n\n";
    
    int reward_score = 50 + (player.stage * 10);
    score += reward_score;
    cout << "Gained " << reward_score << " points! Total: " << score << "\n\n";
    
    cout << "Choose card reward:\n";
    vector<Card> rewards = Cardfactory::create_reward_card(3);
    
    for (int i = 0; i < rewards.size(); i++) {
        cout << "  " << (i + 1) << ". " << rewards[i].getName() 
             << " - " << rewards[i].getDescription() << "\n";
    }
    cout << "  4. Skip\n\n";
    
    int choice;
    cin >> choice;
    
    if (choice >= 1 && choice <= 3) {
        player.cards.push_back(rewards[choice - 1]);
        cout << "Added " << rewards[choice - 1].getName() << "!\n";
    }
    
    player.heal(5);
    cout << "Healed 5 HP. Now: " << player.hp << "/" << player.max_hp << "\n";
}

// End turn cleanup for the older helper flow.
void end_player_turn(Player &player) {
    player.block = 0;
    cout << "End turn. Block reset.\n";
}
