#include "Deck.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>

using namespace std;

void printDeck(const vector<Card>& deck) {          //This function print the unshuffled card
    for (int i = 0; i < deck.size(); i++) {         
        cout << i + 1 << ". " << deck[i].getName() << endl;
    }
}

void shuffleDeck(vector<Card>& deck) {          //This function shuffles the card
    for (int i = deck.size() - 1; i > 0; i--) { 
        int random_index = rand() % (i + 1);
        swap(deck[i], deck[random_index]);
    }
}
