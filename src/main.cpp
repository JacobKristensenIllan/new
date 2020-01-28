#include "vote.h"
#include "election.h"
#include <fstream>
#include <iostream>
#include <chrono>

using namespace std;

int main(){
    
    auto t1 = std::chrono::high_resolution_clock::now(); //this goes directly below main()
    
    fstream in("votes.txt");
    election my_election = read_votes(in);
    // int count stores the round number (each round the candidate with the least first_pref is removed)
    int count = 1;
    // boolean to condition the loop to iterate
    bool majority_reached = false;
    
    // loop must print each round and then operate on the information of a majority existing or lack thereof
    while(!majority_reached){
        auto v = my_election.ranked_candidates();
        // variable holding the number of votes
        auto vote_num = my_election.vote_count();
        // most voted candidate
        auto leader = v[0];
        // least voted candidate
        auto last = v[v.size()-1];
        // output round number and number of votes
        cout << "Round " << count << ": " << vote_num << " votes" << '\n';
        // print out the number of first preference votes for each candidate
        cout << "First preferences:" << '\n';
        typedef vector<double>::size_type vec_size;
        for(vec_size i = 0; i < v.size(); i++){
            cout << "  Candidate " << v[i].first << ": " << v[i].second << '\n';
        }
        // if no majority is found:
        if(leader.second <= vote_num/2){
            candidate last_candidate = last.first;
            my_election.eliminate(last_candidate);
            cout << "Candidate " << last_candidate << " is eliminated." << '\n' << '\n';
        }
        // if a majority exists:
        else{
            cout << "Candidate " << leader.first << " is selected." << '\n' << '\n';
            majority_reached = true;
        }
        count += 1;
    }
    
    auto t2 = std::chrono::high_resolution_clock::now(); //this goes a line above your final return
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count(); //this goes directly above the final return
    cout << duration << '\n';
    return 0;
}
