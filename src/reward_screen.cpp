#include "../include/reward_screen.h"
#include "../include/main.h"
#include "../include/Cardfactory.h"
#include <iostream>

using namespace std;

void show_reward_screen(Player& player, int& score) {
    print_sep_line();
    cout << "=== Battle Complete! ===\n\n";
    
    int battle_score = 100 + (player.stage * 10);
    score += battle_score;
    cout << "Score: " << score << "\n\n";
    
    cout << "Choose a card:\n\n";
    vector<Card> rewards = Cardfactory::create_reward_card(3);
    
    for (size_t i = 0; i < rewards.size(); i++) {
        cout << "  " << (i + 1) << ". " << rewards[i].getName() 
             << " (Cost:" << rewards[i].getCost() << ") - " 
             << rewards[i].getDescription() << "\n";
    }
    cout << "  4. Skip\n\n";
    
    int choice = read_int();
    if (choice >= 1 && choice <= 3) {
        player.cards.push_back(rewards[choice - 1]);
        cout << "\nAdded " << rewards[choice - 1].getName() << "!\n";
    }
    
    player.heal(5);
    cout << "\nHealed 5 HP. HP: " << player.hp << "/" << player.max_hp << "\n";
    cout << "\nPress Enter...";
    cin.ignore();
    cin.get();
}

void show_score_summary(int score, int floor, int difficulty) {
    print_sep_line();
    cout << "=== Run Complete ===\n\n";
    cout << "Final Score: " << score << "\n";
    cout << "Floors: " << floor << "\n";
    cout << "Difficulty: " << difficulty << "\n";
    
    float multiplier = (difficulty == 1) ? 0.8 : (difficulty == 3) ? 1.5 : 1.0;
    cout << "Multiplier: x" << multiplier << "\n";
    cout << "Adjusted: " << (int)(score * multiplier) << "\n";
}