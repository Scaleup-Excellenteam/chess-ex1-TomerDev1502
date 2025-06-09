#pragma once
#include "Move.h"
#include <ostream>


struct ScoredMove {
    Move move;
    int  score;

    std::string toString() const {
        // row = 'a'+fromRow, col = '1'+fromCol
        char rf = char('a' + move.fromRow);
        char cf = char('1' + move.fromCol);
        char rt = char('a' + move.toRow);
        char ct = char('1' + move.toCol);
        return std::string{ rf, cf, rt, ct };
    }
};


struct ScoredMoveComparator {
    bool operator()(ScoredMove const& a, ScoredMove const& b) const {
        return a.score > b.score;
    }
};



