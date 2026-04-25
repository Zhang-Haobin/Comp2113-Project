#include <string>

using namespace std;

// This class stores the information of one card.
// It only keeps card data and does not handle battle logic.
class Card {
private:
    string name;         // card name
    string description;  // card description
    string type;         // card type, such as Attack / Skill / Utility
    int cost;            // energy cost
    int value;           // main number of the card effect

public:
    // Create a default card
    Card();

    // Create a card with full information
    Card(string name, string type, int cost, int value, string description);

    // Read card information
    string getName() const;
    string getDescription() const;
    string getType() const;
    int getCost() const;
    int getValue() const;

    // Check whether current energy is enough
    bool isPlayable(int currentEnergy) const;

    // These functions are card templates.
    // If you want to add a new card, add another createXXX() function.
    static Card createStrike();
    static Card createDefend();
    static Card createHeal();
};
