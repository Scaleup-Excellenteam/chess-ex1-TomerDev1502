#pragma once
#include "Move.h"


struct ScoredMove {
    Move move;
    int  score;
};


struct ScoredMoveComparator {
    bool operator()(ScoredMove const& a, ScoredMove const& b) const {
        return a.score > b.score;
    }
};
