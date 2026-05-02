#ifndef EVENT_SCREEN_H
#define EVENT_SCREEN_H

#include "player.h"

using namespace std;

// Event kinds used by the random event room.
enum class EventType {
    HealEvent, DamageEvent, CardRemovalEvent, CardGainEvent, MysteryEvent
};

void trigger_random_event(Player& player, int& score);  // roll one event and show it
void show_event_result(Player& player, EventType type, int& score);  // actually change HP/cards/score

#endif
