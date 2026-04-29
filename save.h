#ifndef SAVE_H
#define SAVE_H

using namespace std;

struct record{

    int best_score = 0;
    int highest_floor = 0;
    int total_wins = 0;
    int total_losses = 0;

    void reset_record();
    
    int get_total_game();

    double win_rate();
};




record get_record();

bool save_record(const record& record);

void update_record(int current_score, int current_floor,bool player_win);

void print_record();





#endif 
