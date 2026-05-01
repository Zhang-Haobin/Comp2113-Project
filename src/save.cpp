#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

#include "../include/save.h"

using namespace std;

const string save_file = "../save.txt";

void record::reset_record(){
    best_score = 0;
    highest_floor = 0;
    total_wins = 0;
    total_losses = 0;
}


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

void print_record(){
    record record = get_record();
    cout<<endl;
    cout << "=== Game Record ===" << endl;
    cout << "Best Score: " << record.best_score << endl;
    cout << "Highest Floor: " << record.highest_floor << endl;
    cout << "Total Wins: " << record.total_wins << endl;
    cout << "Total Losses: " << record.total_losses << endl;


}

int record::get_total_game(){
    return total_wins + total_losses;
}

double record::win_rate(){
    double total = get_total_game();
    if (total == 0){
        return 0;
    }
    return total_wins/total*100;

}




