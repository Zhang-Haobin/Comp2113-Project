#include "../include/event_screen.h"
#include "../include/main.h"
#include "../include/Cardfactory.h"
#include <iostream>
#include <cstdlib>
#include <limits>

using namespace std;

void trigger_random_event(Player& player, int& score) {
    print_sep_line();
    cout << "=== Random Event ===\n\n";
    
    int roll = rand() % 100;
    EventType type;
    
    if (roll < 25) {
        type = EventType::HealEvent;
        cout << "Found a healing fountain!\n";
    }
    else if (roll < 45) {
        type = EventType::DamageEvent;
        cout << "Triggered a trap!\n";
    }
    else if (roll < 60) {
        type = EventType::CardRemovalEvent;
        cout << "Merchant offers card removal.\n";
    }
    else if (roll < 80) {
        type = EventType::CardGainEvent;
        cout << "Found a rare card!\n";
    }
    else {
        type = EventType::MysteryEvent;
        cout << "Strange light surrounds you...\n";
    }
    
    show_event_result(player, type, score);
    cout << "\nPress Enter...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void show_event_result(Player& player, EventType type, int& score) {
    switch(type) {
        case EventType::HealEvent: {
            int heal = 10 + (rand() % 11);
            player.heal(heal);
            cout << "\nHealed " << heal << " HP! Now: " << player.hp << "/" << player.max_hp << "\n";
            break;
        }
        case EventType::DamageEvent: {
            int dmg = 5 + (rand() % 11);
            player.hurt(dmg);
            cout << "\nTook " << dmg << " damage! HP: " << player.hp << "/" << player.max_hp << "\n";
            break;
        }
        case EventType::CardRemovalEvent: {
            if (player.cards.empty()) {
                cout << "\nNo cards to remove!\n";
                break;
            }
            cout << "\nRemove a card:\n";
            for (size_t i = 0; i < player.cards.size(); i++) {
                cout << "  " << (i + 1) << ". " << player.cards[i].getName() << "\n";
            }
            int choice = read_int();
            if (choice >= 1 && choice <= (int)player.cards.size()) {
                cout << "Removed " << player.cards[choice - 1].getName() << "\n";
                player.cards.erase(player.cards.begin() + (choice - 1));
            }
            break;
        }
        case EventType::CardGainEvent: {
            Card new_card = Cardfactory::create_random_card();
            player.cards.push_back(new_card);
            cout << "\nGained: " << new_card.getName() << " - " << new_card.getDescription() << "\n";
            break;
        }
        case EventType::MysteryEvent: {
            if (rand() % 2 == 0) {
                score += 50;
                cout << "\nGained 50 points!\n";
            } else {
                player.hurt(8);
                cout << "\nTook 8 damage! HP: " << player.hp << "\n";
            }
            break;
        }
    }
    score += 10;
    cout << "Event bonus: +10. Score: " << score << "\n";
}
