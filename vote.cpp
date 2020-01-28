#include "vote.h"
#include <vector>
#include <stdexcept>

using namespace std;

// initialize vote
vote::vote(const std::vector<candidate> &prefs): v(prefs){}

// returns true if the vote has no preferences left
bool vote::spent() const{
    return v.size() == 0;
}

// returns the current first preference of the vote. Clients may only call this member function if spent() is false
candidate vote::first_preference() const{
    if (spent())
        throw domain_error("Cadidate is spent");
    return *v.cbegin();
}


// removes any occurrence of the named candidate from the vote
void vote::discard(candidate c){
    for(int i = 0; i < v.size(); i++){
        if(v[i] == c){
            v.erase(v.begin()+i);
            break;
        }
    }
    //v.erase(remove(v.begin(), v.end(), c), v.end());
}
