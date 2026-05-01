#ifndef EVENT_SCREEN_H
#define EVENT_SCREEN_H

#include "player.h"

using namespace std;

enum class EventType {
    HealEvent, DamageEvent, CardRemovalEvent, CardGainEvent, MysteryEvent
};

void trigger_random_event(Player& player, int& score);  // Main event entry
void show_event_result(Player& player, EventType type, int& score);  // Apply effects

#endif