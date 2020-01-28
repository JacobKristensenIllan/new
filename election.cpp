#include "election.h"
#include <list>
#include <vector>
#include <sstream>
#include <map>

using namespace std;

// election constructor
election::election(){}

// adds a vote to the collection
void election::add_vote(const vote &v){
    collection.push_back(v);
}

// returns the number of votes currently left
int election::vote_count() const{
    int n  = collection.size();
    return n;
}

// removes any occurrence of the named candidate from each vote, and removes any votes that are now spent
void election::eliminate(candidate c){
    auto n = collection.size();
    typedef vector<vote>::size_type vec_size;
    // loop applies discard(c) to each one of the votes, removing the named preference
    for(vec_size i = 0; i < n; i++){
        collection[i].discard(c);
        if (collection[i].spent()){
            swap(collection[i], collection[n-1]);
            collection.pop_back();
            n -= 1;
            //collection.erase(remove_if(collection.begin(), collection.end(), [] (vote v) {return v.spent();}), collection.end());
        }
    }
}
// returns a collection of candidates left in the election paired with the number of first preferences each has, in decreasing order of that number
vector<pair<candidate, int>> election::ranked_candidates() const{
    map<candidate, int> global_score;
    vector<pair<candidate, int>> score_global;
    auto n = collection.size();
    typedef vector<vote>::size_type vec_size;
    for(vec_size i = 0; i < n; i++){
        candidate prefered = collection[i].first_preference();
        ++global_score[prefered];
    }
    for(const auto &s : global_score){
        score_global.push_back(make_pair(s.first, s.second));
    }
    sort(score_global.begin(), score_global.end(), [] (const pair<candidate, int> &a, const pair<candidate, int> &b){return (a.second > b.second);});
    return score_global;
}

// reads the votes of an election in the above format
election read_votes(istream &in){
    election my_election;
    string line;
    while(getline(in, line)){
        stringstream s(line);
        vector<candidate> preferences;
        candidate pref;
        while(s >> pref)
            preferences.push_back(pref);
        vote my_vote(preferences);
        my_election.add_vote(my_vote);
    }
    return my_election;
}
