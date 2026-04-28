#ifndef DECK_H
#define DECK_H

#include <vector>
#include "card.h"

using namespace std;

void printDeck(const vector<Card>& deck);
void shuffleDeck(vector<Card>& deck);

#endif // ifndef DECK_H
