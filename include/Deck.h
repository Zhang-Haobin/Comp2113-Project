#ifndef DECK_H
#define DECK_H

#include <vector>
#include "Card.h"

using namespace std;

// Print the deck in numbered order. Mostly useful when showing choices to the player.
void printDeck(const vector<Card>& deck);

// Shuffle the deck in-place before drawing cards.
void shuffleDeck(vector<Card>& deck);

#endif // ifndef DECK_H
