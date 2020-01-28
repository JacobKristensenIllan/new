#ifndef election_h
#define election_h

#include <vector>
#include <istream>
#include "vote.h"

class election{
    std::vector<vote> collection;
public:
    // election constructor
    election();
    // adds a vote to the collection
    void add_vote(const vote &v);
    // returns the number of votes currently left
    int vote_count() const;
    // removes any occurrence of the named candidate from each vote, and removes any votes that are now spent
    void eliminate(candidate c);
    // returns a collection of candidates left in the election paired with the number of first preferences each has, in decreasing order of that number
    std::vector<std::pair<candidate, int>> ranked_candidates() const;
};

// reads the votes of an election in the above format
election read_votes(std::istream &in);

#endif
