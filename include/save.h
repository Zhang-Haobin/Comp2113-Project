#ifndef SAVE_H
#define SAVE_H

using namespace std;

// Long-term record, not the current run save.
// The current run is handled by GameState instead.
struct record{

    int best_score = 0;
    int highest_floor = 0;
    int total_wins = 0;
    int total_losses = 0;

    // Clear everything back to zero.
    void reset_record();
    
    // Wins + losses, used for win rate.
    int get_total_game();

    // Return a percentage. If no games were played, it just returns 0.
    double win_rate();
};

// Read the long-term record file. Missing file just means empty record.
record get_record();

// Write the long-term record file.
bool save_record(const record& record);

// Update best score/stage and win/loss count after a run ends.
void update_record(int current_score, int current_floor,bool player_win);

// Print records on the record screen.
void print_record();





#endif 
