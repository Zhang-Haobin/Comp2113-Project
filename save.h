#ifndef SAVE_H
#define SAVE_H

using namespace std;

struct Record {
    int best_score = 0;
    int highest_floor = 0;
    int total_wins = 0;
    int total_losses = 0;

    void reset_record();
    int get_total_game();
    double win_rate();
};

Record get_record();
bool save_record(const Record& record);
void update_record(int current_score, int current_floor, bool player_win);
void print_record();

// todo: maybe add a current battle state save
//       if enough time

#endif // ifndef SAVE_H
