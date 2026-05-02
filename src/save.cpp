#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

#include "../include/main.h"
#include "../include/save.h"

using namespace std;

const string save_file = "save.txt";

// Reset the permanent record, not the current run.
void record::reset_record(){
    best_score = 0;
    highest_floor = 0;
    total_wins = 0;
    total_losses = 0;
}


// Read best score / best floor / wins / losses from save.txt.
record get_record(){
    record record;

    ifstream fin(save_file);
    if (!fin){
        return record;
    }

    fin>>record.best_score;
    fin>>record.highest_floor;
    fin>>record.total_wins;
    fin>>record.total_losses;
    
    fin.close();
    return record;
    

}

// Write the permanent record back to save.txt.
bool save_record(const record& record) {
    ofstream fout(save_file);

    if (!fout) {
        return false;
    }

    fout << record.best_score << endl;
    fout << record.highest_floor << endl;
    fout << record.total_wins << endl;
    fout << record.total_losses << endl;

    fout.close();
    return true;
}


// Called once when a run ends, so record numbers stay up to date.
void update_record(int current_score, int current_floor, bool player_won) {
    record record = get_record();

    if (current_score > record.best_score) {
        record.best_score = current_score;
    }

    if (current_floor > record.highest_floor) {
        record.highest_floor = current_floor;
    }

    if (player_won) {
        record.total_wins++;
    } else {
        record.total_losses++;
    }

    save_record(record);
}

// Shows the record screen from the main menu.
void print_record(){
    record record = get_record();
    cout << "==== Game Record ====\n";
    cout << "Best score: " << record.best_score
         << " | Best stage: " << record.highest_floor
         << " | Wins: " << record.total_wins
         << " | Losses: " << record.total_losses << "\n";
    cout << "Win rate: " << record.win_rate() << "%\n";
}

// Total finished runs.
int record::get_total_game(){
    return total_wins + total_losses;
}

// Avoid divide-by-zero if nobody has finished a game yet.
double record::win_rate(){
    double total = get_total_game();
    if (total == 0){
        return 0;
    }
    return total_wins/total*100;

}
