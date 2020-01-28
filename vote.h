#ifndef vote_h
#define vote_h

#include <vector>

typedef unsigned int candidate;

class vote{
    std::vector<candidate> v;
    
public:
    // class vote constuctor
    vote(const std::vector<candidate> &prefs);
    // returns true if the vote has no preferences left
    bool spent() const;
    // returns the current first preference of the vote. Clients may only call this member function if spent() is false
    candidate first_preference() const;
    // removes any occurrence of the named candidate from the vote
    void discard(candidate c);
    
};


#endif
